#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "../../../include/libbase64.h"
#include "../../tables/tables.h"
#include "../../codecs.h"
#include "config.h"
#include "../../env.h"

#if BASE64_WORDSIZE == 32
#  include "32/enc_loop.c"
#elif BASE64_WORDSIZE == 64
#  include "64/enc_loop.c"
#endif

#if BASE64_WORDSIZE >= 32
#  include "32/dec_loop.c"
#endif

BASE64_ENC_FUNCTION(plain)
{
	#include "enc_head.c"
#if BASE64_WORDSIZE == 32
	enc_loop_generic_32(&s, &slen, &o, &olen);
#elif BASE64_WORDSIZE == 64
	enc_loop_generic_64(&s, &slen, &o, &olen);
#endif
	#include "enc_tail.c"
}

BASE64_ENC_FUNCTION(plain_url)
{
	#include "enc_head.c"
#if BASE64_WORDSIZE == 32
	enc_loop_generic_32_url(&s, &slen, &o, &olen);
#elif BASE64_WORDSIZE == 64
	enc_loop_generic_64_url(&s, &slen, &o, &olen);
#endif
	#include "enc_tail_url.c"
}

BASE64_DEC_FUNCTION(plain)
{
	#include "dec_head.c"
#if BASE64_WORDSIZE >= 32
	dec_loop_generic_32(&s, &slen, &o, &olen);
#endif
	#include "dec_tail.c"
}

BASE64_DEC_FUNCTION(plain_url)
{
	#include "dec_head_url.c"
#if BASE64_WORDSIZE >= 32
	dec_loop_generic_32_url(&s, &slen, &o, &olen);
#endif
	#include "dec_tail_url.c"
}
