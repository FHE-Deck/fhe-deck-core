#include "ciphertexts/vector_ciphertext.h"
 
using namespace FHEDeck;


int32_t VectorCTParam::size()const{
    return m_size;
}
 
std::shared_ptr<VectorCTParam> VectorCTSK::vector_ct_param()const{
    return m_vector_ct_param;
}


std::shared_ptr<VectorCTParam> GadgetVectorCTSK::vector_ct_param()const{
    return m_vector_ct_param;
}