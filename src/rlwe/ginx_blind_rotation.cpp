#include "ginx_blind_rotation.h"

using namespace fhe_deck;

 


GINXBlindRotationKey::~GINXBlindRotationKey(){  
    if(is_init){  
        delete[] u;
        delete[] bk; 
    }  
}


GINXBlindRotationKey::GINXBlindRotationKey(std::shared_ptr<RLWEGadgetSK> rlwe_gadget_sk, std::shared_ptr<LWESK> lwe_sk){
    this->rlwe_gadget_param = rlwe_gadget_sk->gadget_param;
    this->lwe_par = lwe_sk->param; 
    
    this->rotation_size = this->rlwe_gadget_param->rlwe_param->N * 2;
    this->actual_rotation_size = this->rlwe_gadget_param->rlwe_param->N;
    LWEParam lwe_par_tiny = lwe_par->modulus_switch(actual_rotation_size);
    this->actual_lwe_par = std::shared_ptr<LWEParam>(new LWEParam(lwe_par_tiny.n, lwe_par_tiny.Q, lwe_par_tiny.key_d, lwe_par_tiny.stddev));

    this->next_acc = RLWECT(this->rlwe_gadget_param->rlwe_param);
    long *ext_s; 
    this->key_d = lwe_par->key_d;
    if(key_d == binary){   
        ext_s = this->init_binary_extended_lwe_key(lwe_sk); 
    }else{  
        ext_s = this->init_ternary_extended_lwe_key(lwe_sk);
    }    
    blind_rotation_key_gen(rlwe_gadget_sk, ext_s);  
    is_init = true;
    delete[] ext_s; 
}



GINXBlindRotationKey::GINXBlindRotationKey(const GINXBlindRotationKey &other){
    this->rlwe_gadget_param = other.rlwe_gadget_param;
    this->lwe_par = other.lwe_par; 

    LWEParam lwe_par_tiny = lwe_par->modulus_switch(this->rlwe_gadget_param->rlwe_param->N);
    this->actual_lwe_par = std::shared_ptr<LWEParam>(new LWEParam(lwe_par_tiny.n, lwe_par_tiny.Q, lwe_par_tiny.key_d, lwe_par_tiny.stddev));

    this->next_acc = RLWECT(this->rlwe_gadget_param->rlwe_param);
    this->key_d = lwe_par->key_d;
    if(this->key_d == binary){  
        init_binary_key(); 
    }else{ 
        init_ternary_key();
    } 
    copy_blind_rotation_key(other.bk);
    is_init = true;
}

    
GINXBlindRotationKey& GINXBlindRotationKey::operator=(const GINXBlindRotationKey other){
    this->rlwe_gadget_param = other.rlwe_gadget_param;
    this->lwe_par = other.lwe_par; 

    LWEParam lwe_par_tiny = lwe_par->modulus_switch(this->rlwe_gadget_param->rlwe_param->N);
    this->actual_lwe_par = std::shared_ptr<LWEParam>(new LWEParam(lwe_par_tiny.n, lwe_par_tiny.Q, lwe_par_tiny.key_d, lwe_par_tiny.stddev));

    this->next_acc = RLWECT(this->rlwe_gadget_param->rlwe_param);
    this->key_d = lwe_par->key_d;
    if(this->key_d == binary){  
        init_binary_key(); 
    }else{ 
        init_ternary_key();
    } 
    copy_blind_rotation_key(other.bk);
    is_init = true;
    return *this;
}  
 


void GINXBlindRotationKey::blind_rotate(std::shared_ptr<BlindRotateOutput> out, long* lwe_ct_in, std::shared_ptr<AbstractAccumulator> acc, GadgetMulMode mode){    
    std::shared_ptr<RotationPolyAccumulator> acc_msg = std::dynamic_pointer_cast<RotationPolyAccumulator>(acc);  
    
    // Set curr_acc.a to zero
    for(int i = 0; i < rlwe_gadget_param->rlwe_param->N; ++i){
        out->rlwe_ct->a.coefs[i] = 0;
    }   
 
    acc_msg->rot_poly.negacyclic_rotate(&out->rlwe_ct->b, lwe_ct_in[0]); 
      
    if(key_d==binary){     
        for(int i = 0; i < lwe_par->n; ++i){    
            out->rlwe_ct->negacyclic_rotate(&next_acc, lwe_ct_in[i+1]);   
            next_acc.sub(&next_acc, out->rlwe_ct);      
            bk[i].mul(&next_acc, &next_acc, mode);    
            next_acc.add(out->rlwe_ct, out->rlwe_ct); 
        } 
    } 
    else if(key_d==ternary){   
        // Rotatate back (multipliation by X^{-ct[i+1]}) and mul with bk_eval[i]
        long back_rotations;
         for(int i = 0; i < lwe_par->n; ++i){  
            back_rotations = Utils::integer_mod_form(-lwe_ct_in[i+1], lwe_par->Q); 
            out->rlwe_ct->negacyclic_rotate(&next_acc, back_rotations);
            next_acc.sub(&next_acc, out->rlwe_ct);  
            bk[i].mul(out->rlwe_ct, &next_acc, mode);
            out->rlwe_ct->add(out->rlwe_ct, out->rlwe_ct);  
        } 
        // Rotatate forward (multipliation by X^{ct[i+1]}) and mul with bk_eval[lwe_par.n+i]
         for(int i = 0; i < lwe_par->n; ++i){ 
            out->rlwe_ct->negacyclic_rotate(&next_acc, back_rotations);
            next_acc.sub(&next_acc, out->rlwe_ct);  
            bk[lwe_par->n+i].mul(out->rlwe_ct, &next_acc, mode);
            out->rlwe_ct->add(out->rlwe_ct, out->rlwe_ct);   
        }
    }else{ 
        throw std::logic_error("GINXBlindRotationKey::blind_rotate: key_d not supported!");
    } 
}

std::shared_ptr<BlindRotateOutput> GINXBlindRotationKey::init_blind_rotate_output(){ 
    RLWECT* out = new RLWECT(rlwe_gadget_param->rlwe_param);
    out->set_computing_engine();
    return std::shared_ptr<BlindRotateOutput>(new BlindRotateOutput(out)); 
}


std::shared_ptr<AbstractAccumulator> GINXBlindRotationKey::prepare_accumulator(long (*f)(long message), PlaintextEncoding output_encoding){ 
    RotationPoly poly = RotationPoly(f, this->actual_rotation_size, output_encoding); 
    
    AbstractAccumulator *acc = new RotationPolyAccumulator(poly); 
    return std::shared_ptr<AbstractAccumulator>(acc);  
}

std::shared_ptr<AbstractAccumulator> GINXBlindRotationKey::prepare_accumulator(long (*f)(long message, long plaintext_space), PlaintextEncoding output_encoding){
    RotationPoly poly = RotationPoly(f, this->actual_rotation_size, output_encoding);
    
    AbstractAccumulator *acc = new RotationPolyAccumulator(poly); 
    return std::shared_ptr<AbstractAccumulator>(acc);  
}


void GINXBlindRotationKey::blind_rotation_key_gen(std::shared_ptr<RLWEGadgetSK> rlwe_gadget_sk, long* ext_s){   
    // TODO: Rewrite this part using the Poolynomial class.
    long *ext_key_mono = new long[rlwe_gadget_sk->gadget_param->rlwe_param->N];
    // TODO: This zeroizing is ugly
    for(int i = 0; i < rlwe_gadget_sk->gadget_param->rlwe_param->N; ++i){
        ext_key_mono[i] = 0;
    }

    this->bk = new RLWEGadgetCT[sizeof_ext_s];    
    for(int i = 0; i < sizeof_ext_s; ++i){   
        ext_key_mono[0] = ext_s[i];      
        bk[i] = rlwe_gadget_sk->gadget_encrypt(ext_key_mono); 
    }    
    delete[] ext_key_mono;  
}



void GINXBlindRotationKey::init_binary_key(){
        sizeof_u = 1;
        this->u = new long[sizeof_u];
        u[0] = 1;
        sizeof_ext_s = lwe_par->n;
}

void GINXBlindRotationKey::init_ternary_key(){
        sizeof_u = 2;
        this->u = new long[sizeof_u];
        u[0] = -1;
        u[1] = 1;
        sizeof_ext_s = 2*lwe_par->n; 
}



long* GINXBlindRotationKey::init_binary_extended_lwe_key(std::shared_ptr<LWESK> lwe_sk){
        sizeof_u = 1;
        this->u = new long[sizeof_u];
        u[0] = 1;
        sizeof_ext_s = lwe_par->n;
        long* ext_s = new long[sizeof_ext_s];
        for(int i = 0; i < lwe_par->n; ++i){
            ext_s[i] = lwe_sk->s[i];
        } 
        return ext_s;
}

long* GINXBlindRotationKey::init_ternary_extended_lwe_key(std::shared_ptr<LWESK> lwe_sk){
        sizeof_u = 1;
        this->u = new long[sizeof_u];
        u[0] = 1;
        sizeof_ext_s = lwe_par->n;
        long*  ext_s = new long[sizeof_ext_s];
        for(int i = 0; i < lwe_par->n; ++i){
            ext_s[i] = lwe_sk->s[i];
        } 
        return ext_s;
}


 
void GINXBlindRotationKey::copy_blind_rotation_key(RLWEGadgetCT *bk){
    this->bk = new RLWEGadgetCT[this->sizeof_ext_s];
    for(int i = 0; i < this->sizeof_ext_s; ++i){
        this->bk[i] = bk[i];
    }
}
  