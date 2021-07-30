#include "CompressedMem.h"
#include "Convert.h"

CompressedMem::CompressedMem(const char firstbit){
    bits += firstbit;
    len = 1;
}
/**
 * add 1 bit to bits if can
 * @param bit 	- [in] bit for add '1' or '0'
 * @return 		- true if CompressedMem fill end, false if can fill more
*/
bool CompressedMem::add_bit(const char bit){
    if(true == monochrom){
        if(bits[len - 1] == bit){
            /* monochrom way */
            if((len - 7) < 0b111111){
                bits += bit;
                len++;
            } else {
                return true;
            }
        } else {
            /* have diff color */
            if(len <= 7){
                monochrom = false;
            } else {
                return true;
            }
        }
    }
    if(false == monochrom){
        /* old mask way */
        if(len < 7){
            bits += bit;
            len++;
        } else {
            return true;
        }
    }
    return false;
}

u16 CompressedMem::to_u16(){
    u16 value = 0;
    if(len < 7){
        monochrom = false;
        bits = str(7 - len, '0') + bits;
    }
    if(monochrom){
        value = (1 << 7) | (Convert::char_to_u16(bits[0]) << 6) | (len - 7);
    } else {
        value = Convert::bin_to_u16(bits);
    }
    return value;
}

str CompressedMem::toString(){
#ifdef __DEBUG
    return Convert::u8_to_bin(to_u16());
#else
    return Convert::u16_to_hex(to_u16());
#endif
}

/**
 * todo:
 * @param s - [in] string, that have len more then zero
 * 
 * @return
 */ 
vec_i CompressedMem::from_string(str& s){
    const size_t len = s.length();
    vec_i result;
    CompressedMem cm(s[0]);
    for(u32 i = 1; i < len; i++){
        if(true == cm.add_bit(s[i])){
            result.push_back(cm.to_u16());
            cm = CompressedMem(s[i]);
        }
    }

    if(cm.len != 0){
        result.push_back(cm.to_u16());
    }

    return result;
}

