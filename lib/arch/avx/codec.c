#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include "../../../include/libbase64.h"
#include "../../tables/tables.h"
#include "../../codecs.h"
#include "config.h"
#include "../../env.h"

#if HAVE_AVX
#include <immintrin.h>

#include "../ssse3/dec_reshuffle.c"
#include "../ssse3/dec_loop.c"
#include "../ssse3/enc_translate.c"
#include "../ssse3/enc_reshuffle.c"
#include "../ssse3/enc_loop.c"

#endif	// HAVE_AVX

BASE64_ENC_FUNCTION(avx)
{
#if HAVE_AVX
	#include "../generic/enc_head.c"
	enc_loop_ssse3(&s, &slen, &o, &olen);
	#include "../generic/enc_tail.c"
#else
	BASE64_ENC_STUB
#endif
}

BASE64_ENC_FUNCTION(avx_url)
{
#if HAVE_AVX
	#include "../generic/enc_head.c"
	enc_loop_ssse3_url(&s, &slen, &o, &olen);
	#include "../generic/enc_tail_url.c"
#else
	BASE64_ENC_STUB
#endif
}

BASE64_DEC_FUNCTION(avx)
{
#if HAVE_AVX
	#include "../generic/dec_head.c"
	dec_loop_ssse3(&s, &slen, &o, &olen);
	#include "../generic/dec_tail.c"
#else
	BASE64_DEC_STUB
#endif
}

BASE64_DEC_FUNCTION(avx_url)
{
#if HAVE_AVX
	#include "../generic/dec_head_url.c"
	dec_loop_ssse3_url(&s, &slen, &o, &olen);
	#include "../generic/dec_tail_url.c"
#else
	BASE64_DEC_STUB
#endif
}
