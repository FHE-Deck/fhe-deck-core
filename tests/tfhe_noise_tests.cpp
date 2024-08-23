
/*
#include "fhe_context.h" 
#include "utils.h"

using namespace fhe_deck;


// This test is ment only for bootstrapping without amortization
void tfhe_bootstrap_noise_test(TFHENamedParams name, int test_num){

    std::cout << "Generate Context..." << std::endl;
    FHEContext context;  
    context.generate_context(name);
    
    Ciphertext c1  = context.encrypt(0);  

    auto id = [](long m) -> long {
        return m;
    }; 
   
    // Big modulus
    long Q = context.tfhe_boot_sk.extract_lwe_sk.param->Q;
    // Small modulus (2*N)
    long q = context.tfhe_boot_pk->lwe_par->Q;
    long* lwe_c = context.tfhe_boot_pk->lwe_gadget_param.lwe_param->init_ct(); 

    std::cout << "Q: " << Q << std::endl;
    std::cout << "q: " << q << std::endl;

    RotationPoly lut_identity = context.genrate_lut(id); 
    Ciphertext out;
    long phase;

    long* post_boot_noise = new long[test_num];
    long* post_ks_noise = new long[test_num];
    long* post_ms_noise = new long[test_num];

    std::cout << "Test: " << std::endl;
    for(int i = 0; i < test_num; ++i){
        std::cerr << "\ri: " << i ;
        // new Encryption
        c1  = context.encrypt(0);  
        // Bootstrap noise
        out = context.eval_lut(&c1, lut_identity);
        phase = context.tfhe_boot_sk.extract_lwe_sk.phase(out.lwe_c->ct);
        post_boot_noise[i] = Utils::integer_signed_form(phase, Q);

        // Key Switching
        if(context.tfhe_boot_pk->ks_type == lazy_key_switch){ 
            context.tfhe_boot_pk->lwe_to_lwe_key_switch_lazy(lwe_c, out.lwe_c->ct);  
        }else if(context.tfhe_boot_pk->ks_type == partial_lazy_key_switch){
            context.tfhe_boot_pk->lwe_to_lwe_key_switch_partial_lazy(lwe_c, out.lwe_c->ct);  
        }else{
            context.tfhe_boot_pk->lwe_to_lwe_key_switch(lwe_c, out.lwe_c->ct);  
        } 
        phase = context.tfhe_boot_sk.lwe_gadget_sk.lwe.phase(lwe_c); 
        post_ks_noise[i] = Utils::integer_signed_form(phase, Q);

        // Modulus switching
        context.tfhe_boot_pk->lwe_gadget_param.lwe_param->switch_modulus(lwe_c, lwe_c, context.tfhe_boot_pk->lwe_par); 
        phase = context.tfhe_boot_sk.lwe_sk.phase(lwe_c);
        post_ms_noise[i] = Utils::integer_signed_form(phase, q);
    }
    std::cerr <<  std::endl;

    // Bootstrap noise
    long min = Utils::min(post_boot_noise, test_num);
    long max = Utils::max(post_boot_noise, test_num); 
    double mean = Utils::mean(post_boot_noise, test_num);
    double stddev = Utils::standard_deviation(post_boot_noise, test_num, mean);
    double var = Utils::variance(post_boot_noise, test_num, mean);
    std::cout << "Bootstrap noise: " << std::endl;
    std::cout << "  min: " << min << std::endl;
    std::cout << "  max: " << max << std::endl;
    std::cout << "  log_2(max): " << Utils::power_times(Utils::abs(max), 2) << std::endl;
    std::cout << "  mean: " << (long)mean << std::endl;
    std::cout << "  stddev: " << (long)stddev << std::endl;
    std::cout << "  var: " << (long)var << std::endl;

    // Key Switching
    min = Utils::min(post_ks_noise, test_num);
    max = Utils::max(post_ks_noise, test_num); 
    mean = Utils::mean(post_ks_noise, test_num);
    stddev = Utils::standard_deviation(post_ks_noise, test_num, mean);
    var = Utils::variance(post_ks_noise, test_num, mean);
    std::cout << "Key Switching noise: " << std::endl;
    std::cout << "  min: " << min << std::endl;
    std::cout << "  max: " << max << std::endl;
    std::cout << "  log_2(max): " << Utils::power_times(Utils::abs(max), 2) << std::endl;
    std::cout << "  mean: " << (long)mean << std::endl;
    std::cout << "  stddev: " << (long)stddev << std::endl;
    std::cout << "  var: " << (long)var << std::endl;


    // Modulus switching
    min = Utils::min(post_ms_noise, test_num);
    max = Utils::max(post_ms_noise, test_num); 
    mean = Utils::mean(post_ms_noise, test_num);
    stddev = Utils::standard_deviation(post_ms_noise, test_num, mean);
    var = Utils::variance(post_ms_noise, test_num, mean);
    std::cout << "Modulus Switching noise: " << std::endl;
    std::cout << "  min: " << min << std::endl;
    std::cout << "  max: " << max << std::endl;
    std::cout << "  log_2(max): " << Utils::power_times(Utils::abs(max), 2) << std::endl;
    std::cout << "  mean: " << (long)mean << std::endl;
    std::cout << "  stddev: " << (long)stddev << std::endl;
    std::cout << "  var: " << (long)var << std::endl;

    delete[] post_boot_noise;
    delete[] post_ks_noise;
    delete[] post_ms_noise;

}



*/
int main(){
 
    //tfhe_bootstrap_noise_test(tfhe_11_B, 50);
}

