/***************************************

	Burgerlib base header

	Copyright (c) 1995-2015 by Rebecca Ann Heineman <becky@burgerbecky.com>

	It is released under an MIT Open Source license. Please see LICENSE
	for license details. Yes, you can use it in a
	commercial title without paying anything, just give me a credit.
	Please? It's not like I'm asking you for money!

	Documentation can be found at http://www.burgerbecky.com/burgerlib/docs

	Comments, suggestions, bug fixes, email me at becky@burgerbecky.com

***************************************/

#ifndef __BURGER__
#define __BURGER__
#if defined(__WATCOMC__)
#define BURGER_WATCOM
#define BURGER_ALIGN(x,s) (x)
#define BURGER_PREALIGN(s)
#define BURGER_POSTALIGN(s)
#define BURGER_STRUCT_PACKPUSH
#define BURGER_X86
#define BURGER_LITTLEENDIAN
#define BURGER_ASM _asm
#define BURGER_INLINE inline
#define BURGER_LONGLONG __int64
#if defined(__DOS__)
#define BURGER_MSDOS
#elif defined(__NT__)
#define BURGER_WIN32
#else
#error Watcom is not set with the proper bt=??? parameter. Try WPP386 bt=NT
#endif
#elif defined(__MRC__)
#define BURGER_MRC
#define BURGER_ALIGN(x,s) __align(s) (x)
#define BURGER_PREALIGN(s) __align(s)
#define BURGER_POSTALIGN(s)
#define BURGER_STRUCT_ALIGN
#define BURGER_MAC
#define BURGER_POWERPC
#define BURGER_BIGENDIAN
#define BURGER_CFM
#if (__MRC__ > 0x0300) && (__MRC__ < 0x0700) && __option(longlong)
#define BURGER_LONGLONG long long
#endif
#elif defined(__SC__) && (defined(MPW_CPLUS) || defined(MPW_C))
#define BURGER_APPLESC
#define BURGER_ALIGN(x,s) __align(s) (x)
#define BURGER_PREALIGN(s) __align(s)
#define BURGER_POSTALIGN(s)
#if (__SC__ >= 0x0801)
#define BURGER_STRUCT_ALIGN
#endif
#define BURGER_MAC
#define BURGER_68K
#define BURGER_BIGENDIAN
#if defined(__CFM68K__)
#define BURGER_CFM
#endif
#elif defined(__ICL)
#define BURGER_INTELCOMPILER
#define BURGER_ALIGN(x,s) __declspec(align(s)) (x)
#define BURGER_PREALIGN(s) __declspec(align(s))
#define BURGER_POSTALIGN(s)
#define BURGER_STRUCT_PACKPUSH
#define BURGER_X86
#define BURGER_WIN32
#define BURGER_LITTLEENDIAN
#define BURGER_ANSIAPI __cdecl
#define BURGER_API __fastcall
#define BURGER_FASTCALLENABLED
#define BURGER_INLINE __forceinline
#define BURGER_ASM _asm
#define BURGER_LONGLONG __int64
#elif (defined(__R5900) || defined(__R5900__)) || (defined(__MWERKS__) && defined(__MIPS__))
#define BURGER_SNSYSTEMS
#define BURGER_ALIGN(x,s) (x) __attribute__((aligned(s)))
#define BURGER_PREALIGN(s)
#define BURGER_POSTALIGN(s) __attribute__((aligned(s)))
#define BURGER_STRUCT_PACK
#define BURGER_MIPS
#define BURGER_PS2
#define BURGER_LITTLEENDIAN
#define BURGER_LONGLONG long
#elif (defined(__SN__) && defined(__PPC__)) || (defined(__MWERKS__) && defined(__PPCGEKKO__))
#define BURGER_SNSYSTEMS
#define BURGER_ALIGN(x,s) (x) __attribute__((aligned(s)))
#define BURGER_PREALIGN(s)
#define BURGER_POSTALIGN(s) __attribute__((aligned(s)))
#define BURGER_STRUCT_PACK
#define BURGER_POWERPC
#define BURGER_GEKKO
#if defined(RVL_SDK)
#define BURGER_WII
#else
#define BURGER_GAMECUBE
#endif
#define BURGER_BIGENDIAN
#elif defined(SDK_ARM9) && defined(SDK_TS)
#define BURGER_METROWERKS
#define BURGER_ALIGN(x,s) (x) __attribute__((aligned(s)))
#define BURGER_PREALIGN(s)
#define BURGER_POSTALIGN(s) __attribute__((aligned(s)))
#define BURGER_STRUCT_PACK
#define BURGER_ARM
#define BURGER_DS
#define BURGER_LITTLEENDIAN
#elif defined(ANDROID)
#define BURGER_GNUC
#define BURGER_ARM
#define BURGER_SHIELD
#define BURGER_ANDROID
#define BURGER_LITTLEENDIAN
#define BURGER_INLINE __inline__ __attribute__((always_inline))
#define BURGER_ALIGN(x,s) (x) __attribute__((aligned(s)))
#define BURGER_PREALIGN(s)
#define BURGER_POSTALIGN(s) __attribute__((aligned(s)))
#define BURGER_STRUCT_PACK
#elif defined(_XBOX) || defined(XBOX)
#define BURGER_MSVC
#define BURGER_ALIGN(x,s) __declspec(align(s)) (x)
#define BURGER_PREALIGN(s) __declspec(align(s))
#define BURGER_POSTALIGN(s)
#define BURGER_STRUCT_PACKPUSH
#if !defined(_M_IX86)
#define BURGER_POWERPC
#define BURGER_BIGENDIAN
#define BURGER_XBOX360
#define BURGER_64BITCPU
#else
#define BURGER_X86
#define BURGER_LITTLEENDIAN
#define BURGER_XBOX
#define BURGER_API __fastcall
#define BURGER_FASTCALLENABLED
#endif
#define BURGER_ANSIAPI __cdecl
#define BURGER_INLINE __forceinline
#define BURGER_ASM _asm
#define BURGER_LONGLONG __int64
#elif defined(__CELLOS_LV2__)
#define BURGER_GNUC
#define BURGER_POWERPC
#define BURGER_BIGENDIAN
#define BURGER_PS3
#define BURGER_64BITCPU
#define BURGER_INLINE inline __attribute__((always_inline))
#define BURGER_ALIGN(x,s) __declspec(align(s)) (x)
#define BURGER_PREALIGN(s) __declspec(align(s))
#define BURGER_POSTALIGN(s)
#define BURGER_STRUCT_PACKPUSH
#define BURGER_LONGLONG long long
#elif defined(__ORBIS__)
#define BURGER_LLVM
#define BURGER_AMD64
#define BURGER_LITTLEENDIAN
#define BURGER_PS4
#define BURGER_64BITCPU
#define BURGER_ALIGN(x,s) __declspec(align(s)) (x)
#define BURGER_PREALIGN(s) __declspec(align(s))
#define BURGER_POSTALIGN(s)
#define BURGER_STRUCT_PACKPUSH
#define BURGER_LONGLONG long long
#elif defined(__MWERKS__)
#define BURGER_METROWERKS
#if defined(macintosh) && macintosh
#define BURGER_BIGENDIAN
#define BURGER_STRUCT_ALIGN
#define BURGER_MAC
#if !defined(__POWERPC__)
#define BURGER_68K
#if !defined(NDEBUG) && !defined(_DEBUG)
#if __option(sym)
#define _DEBUG
#else
#define NDEBUG
#endif
#endif
#if defined(__CFM68K) || defined(__CFM68K__)
#define BURGER_CFM
#endif
#else
#define BURGER_POWERPC
#define BURGER_CFM
#define BURGER_ALIGN(x,s) __declspec(align(s)) (x)
#define BURGER_PREALIGN(s) __declspec(align(s))
#define BURGER_POSTALIGN(s)
#endif
#elif defined(__MACH__)
#define BURGER_STRUCT_ALIGN
#define BURGER_MACOSX
#define BURGER_POWERPC
#define BURGER_BIGENDIAN
#elif !defined(__be_os) || (__be_os != __dest_os)
#define BURGER_STRUCT_PACKPUSH
#define BURGER_WIN32
#define BURGER_X86
#define BURGER_LITTLEENDIAN
#if __MWERKS__>=0x3200
#define BURGER_ANSIAPI __cdecl
#define BURGER_API __fastcall
#define BURGER_FASTCALLENABLED
#else
#define BURGER_DECLSPECNAKED asm
#endif
#define BURGER_ALIGN(x,s) __declspec(align(s)) (x)
#define BURGER_PREALIGN(s) __declspec(align(s))
#define BURGER_POSTALIGN(s)
#define BURGER_LONGLONG long long
#else
#define BURGER_BEOS
#define BURGER_STRUCT_ALIGN
#if !defined(__POWERPC__)
#define BURGER_X86
#define BURGER_LITTLEENDIAN
#else
#define BURGER_POWERPC
#define BURGER_BIGENDIAN
#endif
#endif
#elif defined(__GNUC__) && defined(__MACH__) && (defined(__APPLE_CPP__) || defined(__APPLE_CC__) || defined(__NEXT_CPP__))
#define BURGER_GNUC
#define BURGER_ALIGN(x,s) (x) __attribute__((aligned(s)))
#define BURGER_PREALIGN(s)
#define BURGER_POSTALIGN(s) __attribute__((aligned(s)))
#define BURGER_STRUCT_ALIGN
#if defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
#define BURGER_IOS
#else
#define BURGER_MACOSX
#endif
#define BURGER_INLINE __inline__ __attribute__((always_inline))
#if defined(__i386__)
#define BURGER_X86
#define BURGER_LITTLEENDIAN
#define BURGER_API __attribute__((regparm(3)))
#define BURGER_ANSIAPI __attribute((cdecl))
#define BURGER_DECLSPECNAKED __attribute__((naked))
#elif defined(__x86_64__)
#define BURGER_AMD64
#define BURGER_LITTLEENDIAN
#define BURGER_64BITCPU
#define BURGER_DECLSPECNAKED __attribute__((naked))
#elif defined(__ppc64__)
#define BURGER_POWERPC
#define BURGER_BIGENDIAN
#define BURGER_64BITCPU
#elif defined(__ppc__)
#define BURGER_POWERPC
#define BURGER_BIGENDIAN
#elif defined(__arm__)
#define BURGER_ARM
#if defined(__ARM_NEON__)
#define BURGER_NEON
#endif
#define BURGER_LITTLEENDIAN
#elif defined(__arm64__)
#define BURGER_ARM64
#if defined(__ARM_NEON__)
#define BURGER_NEON
#endif
#define BURGER_LITTLEENDIAN
#define BURGER_64BITCPU
#else
#error Unknown CPU
#endif
#elif defined(_MSC_VER) && defined(_M_IX86)
#define BURGER_MSVC
#define BURGER_ALIGN(x,s) __declspec(align(s)) (x)
#define BURGER_PREALIGN(s) __declspec(align(s))
#define BURGER_POSTALIGN(s)
#define BURGER_STRUCT_PACKPUSH
#define BURGER_X86
#define BURGER_LITTLEENDIAN
#define BURGER_WIN32
#define BURGER_ANSIAPI __cdecl
#define BURGER_API __fastcall
#define BURGER_FASTCALLENABLED
#define BURGER_INLINE __forceinline
#define BURGER_ASM _asm
#define BURGER_LONGLONG __int64
#elif defined(_MSC_VER) && defined(_M_AMD64)
#define BURGER_MSVC
#define BURGER_ALIGN(x,s) __declspec(align(s)) (x)
#define BURGER_PREALIGN(s) __declspec(align(s))
#define BURGER_POSTALIGN(s)
#define BURGER_STRUCT_PACKPUSH
#define BURGER_AMD64
#define BURGER_LITTLEENDIAN
#define BURGER_WIN64
#define BURGER_ANSIAPI __cdecl
#define BURGER_API __fastcall
#define BURGER_FASTCALLENABLED
#define BURGER_INLINE __forceinline
#define BURGER_ASM _asm
#define BURGER_LONGLONG __int64
#define BURGER_64BITCPU
#elif defined(__psp2__)
#if defined(__GNUC__)
#define BURGER_GNUC
#endif
#if defined(__SNC__)
#define BURGER_SNSYSTEMS
#endif
#define BURGER_VITA
#define BURGER_ANDROID
#define BURGER_INLINE __inline__ __attribute__((always_inline))
#define BURGER_ALIGN(x,s) (x) __attribute__((aligned(s)))
#define BURGER_PREALIGN(s)
#define BURGER_POSTALIGN(s) __attribute__((aligned(s)))
#define BURGER_STRUCT_ALIGN
#define BURGER_ARM
#define BURGER_NEON
#define BURGER_LITTLEENDIAN
#else
#error Unknown compiler / platform
#endif
#if defined(BURGER_WIN32) || defined(BURGER_WIN64)
#define BURGER_WINDOWS
#endif
#if defined(BURGER_MAC)
#if !defined(TARGET_API_MAC_CARBON) || (TARGET_API_MAC_CARBON==0)
#define BURGER_MACCLASSIC
#else
#define BURGER_MACCARBON
#endif
#endif
#if defined(BURGER_MAC) || defined(BURGER_MACOSX)
#define BURGER_MACOS
#endif
#if !defined(BURGER_API)
#define BURGER_API
#endif
#if !defined(BURGER_ANSIAPI)
#define BURGER_ANSIAPI
#endif
#if !defined(BURGER_MAXINT)
#define BURGER_MAXINT 0x7FFFFFFF
#endif
#if !defined(BURGER_MAXUINT)
#define BURGER_MAXUINT 0xFFFFFFFFU
#endif
#if !defined(BURGER_ASM)
#define BURGER_ASM asm
#endif
#if !defined(BURGER_DECLSPECNAKED)
#define BURGER_DECLSPECNAKED __declspec(naked)
#endif
#if !defined(BURGER_LONGLONG) && !defined(DOXYGEN)
#define BURGER_LONGLONG long long
#endif
#ifndef BURGER_INLINE
#if defined(__cplusplus) || defined(__GNUC__) || defined(__MWERKS__) || defined(DOXYGEN)
#define BURGER_INLINE inline
#elif defined(BURGER_WINDOWS)
#define BURGER_INLINE __inline
#else
#define BURGER_INLINE
#endif
#endif
#ifndef BURGER_ALIGN
#define BURGER_ALIGN(x,s) x
#endif
#ifndef BURGER_PREALIGN
#define BURGER_PREALIGN(s)
#endif
#ifndef BURGER_POSTALIGN
#define BURGER_POSTALIGN(s)
#endif
#if !defined(BURGER_LITTLEENDIAN) && !defined(BURGER_BIGENDIAN)
#if defined(BURGER_X86) || defined(BURGER_AMD64) || defined(BURGER_PS2) || defined(BURGER_IOS) || defined(BURGER_DS)
#define BURGER_LITTLEENDIAN
#else
#define BURGER_BIGENDIAN
#endif
#endif
#if !defined(NULL)
#define NULL 0
#endif
#if !defined(TRUE)
#define TRUE 1
#endif
#if !defined(FALSE)
#define FALSE 0
#endif
#if defined(NDEBUG) && defined(_DEBUG)
#error NDEBUG and _DEBUG are both defined. Choose one or the other
#endif
#if !defined(NDEBUG) && !defined(_DEBUG)
#error NDEBUG nor _DEBUG were defined. Choose one or the other.
#endif
#if defined(BURGER_WINDOWS) || defined(BURGER_MACOS) || defined(BURGER_IOS) || defined(BURGER_SHIELD) || defined(BURGER_LINUX) || defined(DOXYGEN)
#define BURGER_OPENGL_SUPPORTED
#endif
#if defined(BURGER_IOS) || defined(BURGER_SHIELD) || defined(DOXYGEN)
#define BURGER_OPENGLES
#endif
#define BURGER_OFFSETOF(__type,member) (reinterpret_cast<WordPtr>(&(reinterpret_cast<const __type *>(1)->member))-1)
#define BURGER_ARRAYSIZE(x) static_cast<WordPtr>(sizeof(x)/sizeof(x[0]))
#define BURGER_UNUSED(x) (void)(x)
#define BURGER_HASHMACRO(x) #x
#define BURGER_MACRO_TO_STRING(x) BURGER_HASHMACRO(x)
#if defined(DOXYGEN)
#define BURGER_DISABLECOPYCONSTRUCTORS(x) private:
#else
#define BURGER_DISABLECOPYCONSTRUCTORS(x) private: x(x const &); x &operator = (x const &)
#endif
typedef signed char Int8;
typedef unsigned char Word8;
typedef signed short Int16;
typedef unsigned short Word16;
#if defined(BURGER_PS2) || defined(BURGER_64BITCPU)
typedef signed int Int32;
typedef unsigned int Word32;
#else
typedef signed long Int32;
typedef unsigned long Word32;
#endif
typedef signed BURGER_LONGLONG Int64;
typedef unsigned BURGER_LONGLONG Word64;
typedef Word8 Bool;
typedef Int32 Frac32;
typedef Int32 Fixed32;
typedef unsigned int Word;
typedef signed int Int;
#if defined(BURGER_PS2) || defined(BURGER_PSP)
typedef unsigned int Vector_128 __attribute__((mode (TI)));
#elif defined(BURGER_PS3)
#ifndef __VEC_TYPES_H__
#include <vec_types.h>
#endif
typedef vec_float4 Vector_128;
#elif defined(BURGER_PS4)
typedef float Vector_128 __attribute__((__vector_size__(16)));
#elif defined(BURGER_XBOX360)
#ifndef __PPCINTRINSICS_H__
#include <ppcintrinsics.h>
#endif
#ifndef __VECTORINTRINSICS_H__
#include <vectorintrinsics.h>
#endif
typedef __vector4 Vector_128;
#elif defined(BURGER_MSVC) || defined(BURGER_XBOX)
#ifndef _INCLUDED_EMM
#include <emmintrin.h>
#endif
typedef __m128 Vector_128;
#elif defined(BURGER_METROWERKS) && defined(BURGER_X86)
#ifndef _XMMINTRIN_H
#include <xmmintrin.h>
#endif
typedef __m128 Vector_128;
#elif defined(BURGER_ANDROID)
#ifndef __ARM_NEON_H
#include <arm_neon.h>
#endif
typedef float32x4_t Vector_128;
#else
struct Vector_128 {
	float BURGER_ALIGN(m128_f32[4],16);			///< Opaque contents to the 128 bit vector register
};
#endif
#if defined(BURGER_64BITCPU) && !defined(BURGER_XBOX360) && !defined(BURGER_PS3)
typedef Word64 WordPtr;
typedef Int64 IntPtr;
#define BURGER_MAXWORDPTR 0xFFFFFFFFFFFFFFFFULL
#define BURGER_MAXINTPTR 0x7FFFFFFFFFFFFFFFLL
#else
typedef Word32 WordPtr;
typedef Int32 IntPtr;
#define BURGER_MAXWORDPTR 0xFFFFFFFFU
#define BURGER_MAXINTPTR 0x7FFFFFFF
#endif
#if !defined(BURGER_NONEW)
#if defined(BURGER_METROWERKS)
BURGER_INLINE void *operator new(__typeof__(sizeof(0)), void*x) { return x; }
#elif defined(BURGER_MSVC)
#define __PLACEMENT_NEW_INLINE
BURGER_INLINE void* BURGER_ANSIAPI operator new(size_t, void*x) {return x;}
#elif defined(__GNUC__) && defined(__MACH__) && (defined(__APPLE_CPP__) || defined(__APPLE_CC__) || defined(__NEXT_CPP__)) && defined(BURGER_64BITCPU)
BURGER_INLINE void* operator new(unsigned long int,void *x) {return x;}
#elif defined(BURGER_PS4)
BURGER_INLINE void* operator new(unsigned long, void*x) {return x;}
#elif defined(BURGER_ANDROID) || defined(BURGER_SNSYSTEMS)
BURGER_INLINE void* operator new(unsigned int, void*x) {return x;}
#else
BURGER_INLINE void* operator new(WordPtr, void*x) {return x;}
#endif
#endif
namespace Burger {
template<class T>
BURGER_INLINE void SwapVariables(T *pA,T *pB) {
	T tTemp(*pA);
	*pA = *pB;
	*pB = tTemp;
}
}

#ifndef _INC_STDIO
#include <stdio.h>
#endif

#if defined(BURGER_STRUCT_ALIGN)
#pragma options align=native
#elif defined(BURGER_STRUCT_PACKPUSH)
#pragma pack(push,8)
#elif defined(BURGER_STRUCT_PACK)
#pragma pack(8)
#endif

#if defined(__MWERKS__)
#pragma ANSI_strict off
#pragma enumsalwaysint on
#endif

#if defined(BURGER_WATCOM) && !defined(DOXYGEN)
#pragma disable_message(549)		// Disable 'sizeof' operand contains compiler generated information
extern "C" {
namespace std {
__declspec(__watcall) extern double log(double);
__declspec(__watcall) extern double cos(double);
__declspec(__watcall) extern double sin(double);
__declspec(__watcall) extern double tan(double);
__declspec(__watcall) extern double sqrt(double);
__declspec(__watcall) extern double fabs(double);
__declspec(__watcall) extern double pow(double,double);
__declspec(__watcall) extern double atan2(double,double);
__declspec(__watcall) extern double fmod(double,double);
#pragma intrinsic(log,cos,sin,tan,sqrt,fabs,pow,atan2,fmod)
__declspec(__watcall) extern double acos(double);
__declspec(__watcall) extern double asin(double);
__declspec(__watcall) extern double atan(double);
__declspec(__watcall) extern double cosh(double);
__declspec(__watcall) extern double exp(double);
__declspec(__watcall) extern double log10(double);
__declspec(__watcall) extern double sinh(double);
__declspec(__watcall) extern double tanh(double);
#pragma intrinsic(acos,asin,atan,cosh,exp,log10,sinh,tanh)
__declspec(__watcall) extern int abs(int);
__declspec(__watcall) extern long int labs(long int);
#pragma intrinsic(abs,/* div, */ labs)
}
__declspec(__watcall) extern unsigned int _rotl(unsigned int,unsigned int);
__declspec(__watcall) extern unsigned int _rotr(unsigned int,unsigned int);
#pragma intrinsic(_rotl,_rotr)
extern const float g_fBurgerIntMathNearesttable[2];
extern const float g_fBurgerMath65536;
extern void WatcomAssertNothing(void);
#pragma aux WatcomAssertNothing = modify exact [] nomemory;
extern Word16 _bswap16(Word16 uInput);
#pragma aux _bswap16 = "ror ax,8" parm [ax] value [ax] modify exact [ax] nomemory;
extern Word32 _bswap(Word32 uInput);
#pragma aux _bswap = "bswap eax" parm [eax] value [eax] modify exact [eax] nomemory;
extern Word16 BurgerNativeEndianLoadAny16(const Word16 *pInput);
#pragma aux BurgerNativeEndianLoadAny16 = "mov al,byte ptr[edx]" "mov ah,byte ptr[edx+1]" parm [edx] value [ax] modify exact [eax];
extern Word32 BurgerNativeEndianLoadAny32(const Word32 *pInput);
#pragma aux BurgerNativeEndianLoadAny32 = "mov al,byte ptr[edx]" "mov ah,byte ptr[edx+1]" "ror eax,16" "mov al,byte ptr[edx+2]" "mov ah,byte ptr[edx+3]" "ror eax,16" parm [edx] value [eax] modify exact [eax];
extern long _InterlockedExchange(long volatile*,long);
#pragma aux _InterlockedExchange parm [edx] [eax] = "lock xchg eax,[edx]" value [eax] modify exact [eax];
extern long _InterlockedIncrement(long volatile*);
#pragma aux _InterlockedIncrement parm [edx] = "mov eax,1" "lock xadd [edx],eax" "inc eax" value [eax] modify exact [eax];
extern long _InterlockedDecrement(long volatile*);
#pragma aux _InterlockedDecrement parm [edx] = "or eax,0FFFFFFFFH" "lock xadd [edx],eax" "dec eax" value [eax] modify exact [eax];
extern long _InterlockedExchangeAdd(long volatile*,long);
#pragma aux _InterlockedExchangeAdd parm [edx] [eax] = "lock xadd [edx],eax" value [eax] modify exact [eax];
extern long _InterlockedCompareExchange(long volatile*,long,long);
#pragma aux _InterlockedCompareExchange parm [edx] [ecx] [eax] = "lock cmpxchg [edx],ecx" value [eax] modify exact [eax];
extern Int32 BurgerIntMathMul32GetUpper32(Int32 iInputA,Int32 iInputB);
#pragma aux BurgerIntMathMul32GetUpper32 = "imul edx" parm [eax] [edx] value [edx] modify exact [eax edx] nomemory;
extern Int32 BurgerIntMathMul32x32To64Div32(Int32 iInputMulA,Int32 iInputMulB,Int32 iInputDiv);
#pragma aux BurgerIntMathMul32x32To64Div32 = "imul edx" "idiv ebx" parm [eax] [edx] [ebx] value [eax] modify exact [eax edx];
extern Fixed32 BurgerFixedMathMultiply(Fixed32 fInputMulA,Fixed32 fInputMulB);
#pragma aux BurgerFixedMathMultiply = "imul edx" "shrd eax,edx,16" parm [eax] [edx] value [eax] modify exact [eax edx] nomemory;
extern Fixed32 BurgerFixedMathDivide(Fixed32 fInputNumerator,Fixed32 fInputDenominator);
#pragma aux BurgerFixedMathDivide = "mov edx,eax" "shl eax,16" "sar edx,16" "idiv ebx" parm [eax] [ebx] value [eax] modify exact [eax edx] nomemory;
extern Fixed32 BurgerFixedMathReciprocal(Fixed32 fInput);
#pragma aux BurgerFixedMathReciprocal = "cmp ecx,-1" "mov eax,080000000H" "je Done" "dec eax" "cmp ecx,2" "jb Done" "xor eax,eax" "mov edx,1" "idiv ecx" "Done:" parm [ecx] value [eax] modify exact [eax edx] nomemory;
extern Int32 BurgerIntMathFromFloatFloor(float fInput);
#pragma aux BurgerIntMathFromFloatFloor = "sub esp,4" "fadd dword ptr [g_fBurgerIntMathNearesttable]" "fistp dword ptr [esp]" "pop eax" parm [8087] value [eax] modify exact [eax] nomemory;
extern Int32 BurgerIntMathFromFloat(float fInput);
#pragma aux BurgerIntMathFromFloat = "sub esp,4" "fst dword ptr [esp]" "mov eax,[esp]" "shr eax,31" "fadd dword ptr [g_fBurgerIntMathNearesttable+eax*4]" "fistp dword ptr [esp]" "pop eax" parm [8087] value [eax] modify exact [eax] nomemory;
extern Int32 BurgerIntMathFromFloatCeil(float fInput);
#pragma aux BurgerIntMathFromFloatCeil = "sub esp,4" "fadd dword ptr [g_fBurgerIntMathNearesttable+4]" "fistp dword ptr [esp]" "pop eax" parm [8087] value [eax] modify exact [eax] nomemory;
extern Int32 BurgerIntMathFromFloatNearest(float fInput);
#pragma aux BurgerIntMathFromFloatNearest = "sub esp,4" "fistp dword ptr [esp]" "pop eax" parm [8087] value [eax] modify exact [eax] nomemory;
extern void BurgerIntMathFromFloatFloor2(Int32 *pOutput,float fInput);
#pragma aux BurgerIntMathFromFloatFloor2 = "fadd dword ptr [g_fBurgerIntMathNearesttable]" "fistp dword ptr [eax]" parm [eax] [8087];
extern void BurgerIntMathFromFloat2(Int32 *pOutput,float fInput);
#pragma aux BurgerIntMathFromFloat2 = "sub esp,4" "fst dword ptr [esp]" "pop ecx" "shr ecx,31" "fadd dword ptr [g_fBurgerIntMathNearesttable+ecx*4]" "fistp dword ptr [eax]" parm [eax] [8087] modify exact [ecx];
extern void BurgerIntMathFromFloatCeil2(Int32 *pOutput,float fInput);
#pragma aux BurgerIntMathFromFloatCeil2 = "fadd dword ptr [g_fBurgerIntMathNearesttable+4]" "fistp dword ptr [eax]" parm [eax] [8087] modify exact [];
extern void BurgerIntMathFromFloatNearest2(Int32 *pOutput,float fInput);
#pragma aux BurgerIntMathFromFloatNearest2 = "fistp dword ptr [eax]" parm [eax] [8087] modify exact [];
extern Fixed32 BurgerFixedMathFromFloatFloor(float fInput);
#pragma aux BurgerFixedMathFromFloatFloor = "sub esp,4" "fmul dword ptr [g_fBurgerMath65536]" "fadd dword ptr [g_fBurgerIntMathNearesttable]" "fistp dword ptr [esp]" "pop eax" parm [8087] value [eax] modify exact [eax] nomemory;
extern Fixed32 BurgerFixedMathFromFloat(float fInput);
#pragma aux BurgerFixedMathFromFloat = "sub esp,4" "fst dword ptr [esp]" "fmul dword ptr [g_fBurgerMath65536]""mov eax,[esp]" "shr eax,31" "fadd dword ptr [g_fBurgerIntMathNearesttable+eax*4]" "fistp dword ptr [esp]" "pop eax" parm [8087] value [eax] modify exact [eax] nomemory;
extern Fixed32 BurgerFixedMathFromFloatCeil(float fInput);
#pragma aux BurgerFixedMathFromFloatCeil = "sub esp,4" "fmul dword ptr [g_fBurgerMath65536]" "fadd dword ptr [g_fBurgerIntMathNearesttable+4]" "fistp dword ptr [esp]" "pop eax" parm [8087] value [eax] modify exact [eax] nomemory;
extern Fixed32 BurgerFixedMathFromFloatNearest(float fInput);
#pragma aux BurgerFixedMathFromFloatNearest = "sub esp,4" "fmul dword ptr [g_fBurgerMath65536]" "fistp dword ptr [esp]" "pop eax" parm [8087] value [eax] modify exact [eax] nomemory;
extern void BurgerFixedMathFromFloatFloor2(Fixed32 *pOutput,float fInput);
#pragma aux BurgerFixedMathFromFloatFloor2 = "fmul dword ptr [g_fBurgerMath65536]" "fadd dword ptr [g_fBurgerIntMathNearesttable]" "fistp dword ptr [eax]" parm [eax] [8087] modify exact [];
extern void BurgerFixedMathFromFloat2(Fixed32 *pOutput,float fInput);
#pragma aux BurgerFixedMathFromFloat2 = "sub esp,4" "fst dword ptr [esp]" "fmul dword ptr [g_fBurgerMath65536]" "pop ecx" "shr ecx,31" "fadd dword ptr [g_fBurgerIntMathNearesttable+ecx*4]" "fistp dword ptr [eax]" parm [eax] [8087] modify [ecx];
extern void BurgerFixedMathFromFloatCeil2(Fixed32 *pOutput,float fInput);
#pragma aux BurgerFixedMathFromFloatCeil2 = "fmul dword ptr [g_fBurgerMath65536]" "fadd dword ptr [g_fBurgerIntMathNearesttable+4]" "fistp dword ptr [eax]" parm [eax] [8087] modify exact [];
extern void BurgerFixedMathFromFloatNearest2(Fixed32 *pOutput,float fInput);
#pragma aux BurgerFixedMathFromFloatNearest2 = "fmul dword ptr [g_fBurgerMath65536]" "fistp dword ptr [eax]" parm [eax] [8087] modify exact [];
}
#endif
#if defined(BURGER_MSVC) && !defined(DOXYGEN)
extern "C" {
extern double __cdecl fabs(double);
extern double __cdecl sqrt(double);
#pragma intrinsic(fabs,sqrt)
extern Word16 __cdecl _byteswap_ushort(Word16);
extern unsigned long __cdecl _byteswap_ulong(unsigned long);
extern Word64 __cdecl _byteswap_uint64(Word64);
#pragma intrinsic(_byteswap_ushort,_byteswap_ulong,_byteswap_uint64)
extern unsigned int __cdecl _rotl(unsigned int,int);
extern Word64 __cdecl _rotl64(Word64,int);
extern unsigned int __cdecl _rotr(unsigned int,int);
extern Word64 __cdecl _rotr64(Word64,int);
#pragma intrinsic(_rotl,_rotl64,_rotr,_rotr64)
long _InterlockedExchange(long volatile*,long);
long __cdecl _InterlockedIncrement(long volatile*);
long __cdecl _InterlockedDecrement(long volatile*);
long _InterlockedExchangeAdd(long volatile*,long);
long _InterlockedCompareExchange(long volatile*,long,long);
#pragma intrinsic(_InterlockedExchange,_InterlockedIncrement,_InterlockedDecrement,_InterlockedExchangeAdd,_InterlockedCompareExchange)
#if defined(BURGER_64BITCPU)
__int64 _InterlockedExchange64(__int64 volatile*,__int64);
__int64 _InterlockedIncrement64(__int64 volatile*);
__int64 _InterlockedDecrement64(__int64 volatile*);
__int64 _InterlockedExchangeAdd64(__int64 volatile*,__int64);
__int64 _InterlockedCompareExchange64(__int64 volatile*,__int64,__int64);
#pragma intrinsic(_InterlockedExchange64,_InterlockedIncrement64,_InterlockedDecrement64,_InterlockedExchangeAdd64,_InterlockedCompareExchange64)
#if _MSC_VER<1500		// Visual studio 2005 and earlier don't have these SSE type conversions
BURGER_INLINE float _mm_cvtss_f32(__m128 vInput) { return vInput.m128_f32[0]; }
BURGER_INLINE double _mm_cvtsd_f64(__m128d vInput) { return vInput.m128d_f64[0]; }
#endif
#endif
}
#endif
#if defined(BURGER_IOS) && !defined(DOXYGEN)
#endif
#if defined(BURGER_MACOSX) && !defined(DOXYGEN)
#endif
#if defined(BURGER_METROWERKS) && !defined(DOXYGEN)
extern "C" {
#if defined(BURGER_X86)
__inline long _InterlockedExchange(register long volatile*pOutput,register long lValue) { asm { lock xchg lValue,[pOutput] } return lValue; }
__inline long _InterlockedIncrement(register long volatile*pOutput) { register long lTemp=1; asm { lock xadd [pOutput],lTemp } return lTemp+1; }
__inline long _InterlockedDecrement(register long volatile*pOutput) { register long lTemp=-1; asm { lock xadd [pOutput],lTemp } return lTemp-1; }
__inline long _InterlockedExchangeAdd(register long volatile*pOutput,register long lValue) { asm { lock xadd [pOutput],lValue } return lValue; }
__inline long _InterlockedCompareExchange(register long volatile*pOutput,register long lAfter,register long lBefore) { asm { mov eax,lBefore
	lock xadd [pOutput],lAfter
	mov lBefore,eax} return lBefore; }
namespace std {
#if __has_intrinsic(__builtin_fabsf)
extern float __builtin_fabsf(float) __attribute__((nothrow)) __attribute__((const));
#endif
#if __has_intrinsic(__builtin_fabs)
extern double __builtin_fabs(double) __attribute__((nothrow)) __attribute__((const));
#endif
#if __has_intrinsic(__builtin_sqrt)
extern double __builtin_sqrt(double) __attribute__((nothrow)) __attribute__((const));
#endif
#if __has_intrinsic(__builtin___count_leading_zero32)
extern unsigned int __builtin___count_leading_zero32(unsigned int) __attribute__((nothrow)) __attribute__((const));
#endif
#if __has_intrinsic(__builtin___count_trailing_zero32)
extern unsigned int __builtin___count_trailing_zero32(unsigned int) __attribute__((nothrow)) __attribute__((const));
#endif
#if __has_intrinsic(__builtin___count_leading_zero64)
extern unsigned int __builtin___count_leading_zero64(unsigned long long) __attribute__((nothrow)) __attribute__((const));
#endif
#if __has_intrinsic(__builtin___count_bits64)
extern unsigned int __builtin___count_bits64(unsigned long long) __attribute__((nothrow)) __attribute__((const));
#endif
}
#elif defined(BURGER_68K)
Word16 BURGER_INLINE _bswap16(Word16:__D0):__D0 = { 0xE058 };
Word32 BURGER_INLINE _bswap(Word32:__D0):__D0 = { 0xE058, 0x4840, 0xE058 };
#pragma parameter __D1 BurgerIntMathMul32GetUpper32(__D0,__D1)
Int32 BurgerIntMathMul32GetUpper32(Int32 iInputMulA,Int32 iInputMulB) = {0x4c01,0xc01};	// muls.l d1,d1:d0
#pragma parameter __D0 BurgerIntMathMul32x32To64Div32(__D0,__D1,__D2)
Int32 BurgerIntMathMul32x32To64Div32(Int32 iInputMulA,Int32 iInputMulB,Int32 iInputDiv) = {0x4c01,0xc01,0x4c42,0xc01};	// muls.l d1,d1:d0 divs.l ds,d1:d0
extern double __fabs(double x);
extern void* __alloca(unsigned x);
#elif defined(BURGER_POWERPC)
extern double sqrt(double);
float BURGER_INLINE sqrtf(float fInput) { return static_cast<float>(sqrt(fInput)); }
#if __has_intrinsic(__builtin___rotate_left32)
extern unsigned int __builtin___rotate_left32(unsigned int,int) __attribute__((nothrow)) __attribute__((const));
#endif
#if __has_intrinsic(__builtin___rotate_right32)
extern unsigned int __builtin___rotate_right32(unsigned int,int) __attribute__((nothrow)) __attribute__((const));
#endif
#endif
}
#endif
#if defined(BURGER_SNSYSTEMS) && !defined(DOXYGEN)
extern float __builtin_fabsf(float);
extern double __builtin_fabs(double);
extern float __builtin_sqrtf(float);
extern double __builtin_sqrt(double);
extern Word32 __builtin_rol(Word32,const Word32);
extern Word32 __builtin_ror(Word32,const Word32);
extern Word32 __builtin_rev(Word32);
extern Word32 __builtin_clz(Word32);
#endif
namespace Burger {
	typedef int (BURGER_API *ProcAssert)(void *pThis,const char *pCondition,const char *pFilename,Word uLineNumber);
	extern int BURGER_API Assert(const char *pCondition,const char *pFilename,Word uLineNumber);
	extern void BURGER_API AssertRedirect(ProcAssert pAssert,void *pThis);
	extern void BURGER_API Halt(void);
}
#if defined(BURGER_WATCOM) && !defined(DOXYGEN)
#if defined(_DEBUG)
#define BURGER_ASSERT(conditional) ((conditional) ? WatcomAssertNothing() : static_cast<void>(::Burger::Assert(#conditional,__FILE__,__LINE__)))
#define BURGER_ASSERTTEST(conditional) ((conditional) ? TRUE : ::Burger::Assert(#conditional,__FILE__,__LINE__))
#else
#define BURGER_ASSERT(conditional) WatcomAssertNothing()
#define BURGER_ASSERTTEST(conditional) ((conditional) ? TRUE : FALSE)
#endif
#elif defined(_DEBUG) || defined(DOXYGEN)
#define BURGER_ASSERT(conditional) ((conditional) ? static_cast<void>(NULL) : static_cast<void>(::Burger::Assert(#conditional,__FILE__,__LINE__)))
#define BURGER_ASSERTTEST(conditional) ((conditional) ? TRUE : ::Burger::Assert(#conditional,__FILE__,__LINE__))
#else
#define BURGER_ASSERT(conditional) static_cast<void>(NULL)
#define BURGER_ASSERTTEST(conditional) ((conditional) ? TRUE : FALSE)
#endif
#define BURGER_COMPILE_TIME_ASSERT(x) typedef int ThisIsABogusTypeDef ## __LINE__ [(x) * 2 - 1]
namespace Burger {
class Debug {
public:
	static Word BURGER_ANSIAPI Fatal(const char *pMessage,...);
	static void BURGER_ANSIAPI Warning(const char *pMessage,...);
	static void BURGER_ANSIAPI Message(const char *pMessage,...);
	static void BURGER_API String(const char *pMessage);
	static void BURGER_API String(Word32 uInput);
	static void BURGER_API String(Word64 uInput);
	static Word BURGER_API IsDebuggerPresent(void);
};
extern void BURGER_API OkAlertMessage(const char *pMessage,const char *pTitle=NULL);
extern Word BURGER_API OkCancelAlertMessage(const char *pMessage,const char *pTitle=NULL);
}
#if defined(BURGER_WINDOWS) && !defined(DOXYGEN)
struct HINSTANCE__;
struct HWND__;
struct HPALETTE__;
struct HBITMAP__;
struct HDC__;
struct HGLRC__;
struct HICON__;
struct IDirectInputW;
struct IDirectInput8W;
struct IDirectInputDevice2W;
struct IDirectInputDevice8W;
struct IDirectDraw;
struct IDirectDraw2;
struct IDirectDraw4;
struct IDirectDraw7;
struct IDirectDrawSurface;
struct IDirectDrawSurface2;
struct IDirectDrawSurface3;
struct IDirectDrawSurface4;
struct IDirectDrawSurface7;
struct IDirectDrawPalette;
struct IDirectDrawClipper;
struct IDirectDrawColorControl;
struct IDirectDrawGammaControl;
struct IDirect3D9;
struct IDirect3DDevice9;
struct IDirect3DStateBlock9;
struct IDirect3DVertexDeclaration9;
struct IDirect3DVertexShader9;
struct IDirect3DPixelShader9;
struct IDirect3DResource9;
struct IDirect3DBaseTexture9;
struct IDirect3DTexture9;
struct IDirect3DVolumeTexture9;
struct IDirect3DCubeTexture9;
struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;
struct IDirect3DSurface9;
struct IDirect3DVolume9;
struct IDirect3DSwapChain9;
struct IDirect3DQuery9;
struct IDirectSound;
struct IDirectSoundBuffer;
struct IDirectSound3DListener;
struct IDirectSound3DBuffer;
struct IDirectSoundCapture;
struct IDirectSoundCaptureBuffer;
struct IDirectSoundNotify;
struct IDirectSound8;
struct IDirectSoundBuffer8;
struct IDirectSoundCaptureBuffer8;
struct IDirectSoundFXGargle;
struct IDirectSoundFXChorus;
struct IDirectSoundFXFlanger;
struct IDirectSoundFXEcho;
struct IDirectSoundFXDistortion;
struct IDirectSoundFXCompressor;
struct IDirectSoundFXParamEq;
struct IDirectSoundFXWavesReverb;
struct IDirectSoundFXI3DL2Reverb;
struct IDirectSoundCaptureFXAec;
struct IDirectSoundCaptureFXNoiseSuppress;
struct IDirectSoundFullDuplex;
struct ID3DXEffect;
struct ID3DXEffectPool;
struct IUnknown;
struct _DIDATAFORMAT;
struct _D3DPRESENT_PARAMETERS_;
struct _D3DCAPS9;
struct _D3DDISPLAYMODE;
struct _FILETIME;
struct _GUID;
struct tagRECT;
struct tagPOINT;
struct _RTL_CRITICAL_SECTION_DEBUG;
struct _SP_DEVICE_INTERFACE_DATA;
struct _SP_DEVINFO_DATA;
struct _SP_DEVICE_INTERFACE_DETAIL_DATA_A;
struct _SP_DEVICE_INTERFACE_DETAIL_DATA_W;
namespace Burger {
struct CRITICAL_SECTION {
	_RTL_CRITICAL_SECTION_DEBUG *DebugInfo;
	Word32 LockCount;
	Word32 RecursionCount;
	void *OwningThread;
	void *LockSemaphore;
	WordPtr SpinCount;
};
}
#endif
#if defined(BURGER_XBOX360) && !defined(DOXYGEN)
struct Direct3D;
struct D3DDevice;
struct D3DStateBlock;
struct D3DVertexDeclaration;
struct D3DVertexShader;
struct D3DPixelShader;
struct D3DResource;
struct D3DBaseTexture;
struct D3DTexture;
struct D3DVolumeTexture;
struct D3DCubeTexture;
struct D3DArrayTexture;
struct D3DLineTexture;
struct D3DVertexBuffer;
struct D3DIndexBuffer;
struct D3DSurface;
struct D3DVolume;
struct D3DQuery;
struct D3DPerfCounters;
struct D3DPerfCounterBatch;
struct D3DConstantBuffer;
struct D3DCommandBuffer;
struct D3DAsyncCommandBufferCall;
struct D3DOcclusionQueryBatch;
struct _FILETIME;
struct _GUID;
struct tagPOINT;
struct tagRECT;
namespace Burger {
struct CRITICAL_SECTION {
	union {
		Word32 RawEvent[4];
	} Synchronization;
	Word32 LockCount;
	Word32 RecursionCount;
	void *OwningThread;
};
}
#endif
#if defined(BURGER_MACOSX) && !defined(DOXYGEN)
struct Point;
struct Rect;
struct FSRef;
struct UTCDateTime;
struct _NSPoint;
struct _NSSize;
struct _NSRect;
struct CGPoint;
struct CGSize;
struct CGRect;
struct _opaque_pthread_t;
struct _CGLContextObject;
struct _CGLPixelFormatObject;
struct _CGLRendererInfoObject;
struct _CGLPBufferObject;
struct __CFString;
struct __CFDictionary;
struct __IOHIDDevice;
struct __IOHIDElement;
struct __IOHIDValue;
struct __IOHIDManager;
@class NSApplication;
@class NSApplicationDelegate;
@class NSEvent;
@class NSMenu;
@class NSMenuItem;
@class NSOpenGLView;
@class NSScreen;
@class NSString;
@class NSView;
@class NSWindow;
@class NSWindowController;
namespace Burger {
	typedef int sem_t;
	typedef unsigned int semaphore_t;
	typedef unsigned int task_t;
#if defined(BURGER_64BITCPU)
	struct pthread_mutex_t { Word64 m_Opaque[8]; };
	struct pthread_cond_t { Word64 m_Opaque[6]; };
#else
	struct pthread_mutex_t { Word32 m_Opaque[11]; };
	struct pthread_cond_t { Word32 m_Opaque[7]; };
#endif
}
#endif
#if defined(BURGER_MAC) && !defined(DOXYGEN)
struct Point;
struct Rect;
struct FSRef;
struct UTCDateTime;
struct CCrsr;
struct GrafPort;
struct OpaqueDialogPtr;
struct FSSpec;
struct OpaqueCFragConnectionID;
struct OpaqueFSIterator;
#if TARGET_API_MAC_CARBON
typedef struct OpaqueDialogPtr* DialogRef;	///< Alias for DialogRef for MacOS
#else
typedef struct GrafPort *DialogRef;
#endif
#endif
#if defined(BURGER_IOS) && !defined(DOXYGEN)
struct Point;
struct Rect;
struct FSRef;
struct UTCDateTime;
struct CGPoint;
struct CGSize;
struct CGRect;
struct _opaque_pthread_t;
@class EAGLContext;
@class NSObject;
@class UIView;
@class UIWindow;
@class UIImage;
@class UIImageView;
@class UIViewController;
namespace Burger {
	typedef int sem_t;
	typedef unsigned int semaphore_t;
	typedef unsigned int task_t;
#if defined(BURGER_64BITCPU)
	struct pthread_mutex_t { Word64 m_Opaque[8]; };
	struct pthread_cond_t { Word64 m_Opaque[6]; };
#else
	struct pthread_mutex_t { Word32 m_Opaque[11]; };
	struct pthread_cond_t { Word32 m_Opaque[7]; };
#endif
}
#endif
#if defined(BURGER_MSDOS) || defined(DOXYGEN)
namespace Burger {
struct Regs16 {
	Word16 ax;		///< 80x86 ax register
	Word16 bx;		///< 80x86 bx register
	Word16 cx;		///< 80x86 cx register
	Word16 dx;		///< 80x86 dx register
	Word16 si;		///< 80x86 si register
	Word16 di;		///< 80x86 di register
	Word16 bp;		///< 80x86 bp register
	Word16 ds;		///< 80x86 ds segment register
	Word16 es;		///< 80x86 es segment register
	Word16 flags;	///< 80x86 flags register
};
}
#endif
#if defined(BURGER_PS3) && !defined(DOXYGEN)
namespace Burger {
typedef Word32 _sys_sleep_queue_t;
struct sys_lwmutex_lock_info_t {
	volatile Word32 owner;
	volatile Word32 waiter;
};
union sys_lwmutex_variable_t {
	sys_lwmutex_lock_info_t info;
	volatile Word64 all_info;
};
struct sys_lwmutex_t {
	sys_lwmutex_variable_t lock_var;
	Word32 attribute;
	Word32 recursive_count;
	_sys_sleep_queue_t sleep_queue;
	Word32 pad;
};
}
#endif
#if defined(BURGER_PS4) && !defined(DOXYGEN)
struct pthread_mutex;
#endif
#if defined(BURGER_ANDROID) && !defined(DOXYGEN)
namespace Burger {
struct pthread_mutex_t {
	int volatile value;
};
struct sem_t {
	volatile unsigned int count;
};
struct pthread_cond_t {
	int volatile value;
};
}
#endif
#if defined(BURGER_VITA) && !defined(DOXYGEN)
struct SceDateTime;
#endif
namespace Burger {
class SwapEndian {
public:
#if defined(BURGER_WATCOM) || (defined(BURGER_METROWERKS) && defined(BURGER_68K))
static Word16 BURGER_INLINE Load(Word16 uInput) { return _bswap16(uInput); }
static Word32 BURGER_INLINE Load(Word32 uInput) { return _bswap(uInput); }
static Word16 BURGER_INLINE Load(const Word16 *pInput) { return _bswap16(pInput[0]); }
static Word32 BURGER_INLINE Load(const Word32 *pInput) { return _bswap(pInput[0]); }
static void BURGER_INLINE Store(Word16 *pOutput,Word16 uInput) { pOutput[0] = _bswap16(uInput); }
static void BURGER_INLINE Store(Word32 *pOutput,Word32 uInput) { pOutput[0] = _bswap(uInput); }
#elif defined(BURGER_XBOX360) && !defined(DOXYGEN)
static Word16 BURGER_INLINE Load(Word16 uInput) { return _byteswap_ushort(uInput); }
static Word32 BURGER_INLINE Load(Word32 uInput) { return _byteswap_ulong(uInput); }
static Word16 BURGER_INLINE Load(const Word16 *pInput) { return __loadshortbytereverse(0,pInput); }
static Word32 BURGER_INLINE Load(const Word32 *pInput) { return __loadwordbytereverse(0,pInput); }
static void BURGER_INLINE Store(Word16 *pOutput,Word16 uInput) { __storeshortbytereverse(uInput,0,pOutput); }
static void BURGER_INLINE Store(Word32 *pOutput,Word32 uInput) { __storewordbytereverse(uInput,0,pOutput); }
#elif defined(BURGER_POWERPC) && defined(BURGER_METROWERKS)
static Word16 BURGER_INLINE Load(Word16 uInput) { int iResult = __rlwinm(static_cast<int>(uInput),24,24,31);
	iResult = __rlwimi(iResult,static_cast<int>(uInput),8,16,23);
	return static_cast<Word16>(iResult); }
static Word32 BURGER_INLINE Load(Word32 uInput) { int iResult = __rlwinm(static_cast<int>(uInput),8,24,31);
	iResult = __rlwimi(iResult,static_cast<int>(uInput),24,16,23);
	iResult = __rlwimi(iResult,static_cast<int>(uInput),8,8,15);
	iResult = __rlwimi(iResult,static_cast<int>(uInput),24,0,7);
	return static_cast<Word32>(iResult); }
static Word16 BURGER_INLINE Load(const Word16 *pInput) { return static_cast<Word16>(__lhbrx(const_cast<Word16 *>(pInput),0)); }
static Word32 BURGER_INLINE Load(const Word32 *pInput) { return __lwbrx(const_cast<Word32 *>(pInput),0); }
#elif defined(BURGER_X86) && defined(BURGER_METROWERKS)
static Word16 BURGER_INLINE Load(Word16 uInput) {
	return __ror(uInput,8);
}
static Word32 BURGER_INLINE Load(Word32 uInput) {
	asm bswap uInput
	return uInput;
}
static Word16 BURGER_INLINE Load(const Word16 *pInput) {
	return __ror(pInput[0],8);
}
static Word32 BURGER_INLINE Load(const Word32 *pInput) {
	register int uTemp;
	uTemp = static_cast<int>(pInput[0]);
	asm bswap uTemp
	return static_cast<Word32>(uTemp);
}
static void BURGER_INLINE Store(Word16 *pOutput,Word16 uInput) {
	pOutput[0] = __ror(uInput,8);
}
static void BURGER_INLINE Store(Word32 *pOutput,Word32 uInput) {
	asm bswap uInput
	pOutput[0] = uInput;
}
#elif defined(BURGER_INTELCOMPILER)
static Word16 BURGER_INLINE Load(Word16 uInput) { return static_cast<Word16>(_bswap(uInput)>>16); }
static Word32 BURGER_INLINE Load(Word32 uInput) { return _bswap(uInput); }
static Word16 BURGER_INLINE Load(const Word16 *pInput) { return static_cast<Word16>(_bswap(pInput[0])>>16); }
static Word32 BURGER_INLINE Load(const Word32 *pInput) { return _bswap(pInput[0]);}
static void BURGER_INLINE Store(Word16 *pOutput,Word16 uInput) { pOutput[0] = static_cast<Word16>(_bswap(uInput)>>16); }
static void BURGER_INLINE Store(Word32 *pOutput,Word32 uInput) { pOutput[0] = _bswap(uInput); }
#elif (defined(BURGER_X86) || defined(BURGER_AMD64)) && defined(BURGER_MSVC)
static Word16 BURGER_INLINE Load(Word16 uInput) { return _byteswap_ushort(uInput); }
static Word32 BURGER_INLINE Load(Word32 uInput) { return _byteswap_ulong(uInput); }
static Word16 BURGER_INLINE Load(const Word16 *pInput) { return _byteswap_ushort(pInput[0]); }
static Word32 BURGER_INLINE Load(const Word32 *pInput) { return _byteswap_ulong(pInput[0]); }
static void BURGER_INLINE Store(Word16 *pOutput,Word16 uInput) { pOutput[0] = _byteswap_ushort(uInput); }
static void BURGER_INLINE Store(Word32 *pOutput,Word32 uInput) { pOutput[0] = _byteswap_ulong(uInput); }
#else
static Word16 BURGER_API Load(Word16 uInput);
static Word32 BURGER_API Load(Word32 uInput);
static Word16 BURGER_API Load(const Word16 *pInput);
static Word32 BURGER_API Load(const Word32 *pInput);
static void BURGER_API Store(Word16 *pOutput,Word16 uInput);
static void BURGER_API Store(Word32 *pOutput,Word32 uInput);
#endif
#if (defined(BURGER_XBOX360) || ((defined(BURGER_X86) || defined(BURGER_AMD64)) && defined(BURGER_MSVC))) && !defined(DOXYGEN)
static Word64 BURGER_INLINE Load(Word64 uInput) { return _byteswap_uint64(uInput); }
#else
static Word64 BURGER_API Load(Word64 uInput);
#endif
#if defined(BURGER_XBOX360) && !defined(DOXYGEN)
static Word64 BURGER_INLINE Load(const Word64 *pInput) { return __loaddoublewordbytereverse(0,pInput); }
static void BURGER_INLINE Store(Word64 *pOutput,Word64 uInput) { return __storedoublewordbytereverse(uInput,0,pOutput); }
#elif defined(BURGER_AMD64) && defined(BURGER_MSVC)
static Word64 BURGER_INLINE Load(const Word64 *pInput) { return _byteswap_uint64(pInput[0]); }
static void BURGER_INLINE Store(Word64 *pOutput,Word64 uInput) { pOutput[0] = _byteswap_uint64(uInput); }
#else
static Word64 BURGER_API Load(const Word64 *pInput);
static void BURGER_API Store(Word64 *pOutput,Word64 uInput);
#endif
static float BURGER_API Load(float fInput);
static double BURGER_API Load(double dInput);
static float BURGER_API Load(const float *pInput);
static double BURGER_API Load(const double *pInput);
static void BURGER_API Store(float *pOutput,float fInput);
static void BURGER_API Store(double *pOutput,double dInput);
static Word16 BURGER_API LoadAny(const Word16 *pInput);
static Word32 BURGER_API LoadAny(const Word32 *pInput);
static Word64 BURGER_API LoadAny(const Word64 *pInput);
static float BURGER_API LoadAny(const float *pInput);
static double BURGER_API LoadAny(const double *pInput);
static void BURGER_API StoreAny(Word16 *pOutput,Word16 uInput);
static void BURGER_API StoreAny(Word32 *pOutput,Word32 uInput);
static void BURGER_API StoreAny(Word64 *pOutput,Word64 uInput);
static void BURGER_API StoreAny(float *pOutput,float fInput);
static void BURGER_API StoreAny(double *pOutput,double dInput);
static void BURGER_INLINE Fixup(Word16 *pInput) { pInput[0] = Load(pInput); }
static void BURGER_INLINE Fixup(Word32 *pInput) { pInput[0] = Load(pInput); }
#if (defined(BURGER_XBOX360) || defined(BURGER_AMD64)) && !defined(DOXYGEN)
static void BURGER_INLINE Fixup(Word64 *pInput) { pInput[0] = Load(pInput); }
#elif defined(BURGER_POWERPC) && defined(BURGER_METROWERKS)
static void BURGER_INLINE Fixup(Word64 *pInput) {
	Word32 uLow = __lwbrx(pInput,0);
	Word32 uHigh = __lwbrx(pInput,4);
	reinterpret_cast<Word32 *>(pInput)[0] = uHigh;
	reinterpret_cast<Word32 *>(pInput)[1] = uLow;
}
#else
static void BURGER_API Fixup(Word64 *pInput);
#endif
static void BURGER_API FixupAny(Word16 *pInput);
static void BURGER_API FixupAny(Word32 *pInput);
static void BURGER_API FixupAny(Word64 *pInput);
static BURGER_INLINE Int16 Load(Int16 iInput) { return static_cast<Int16>(Load(static_cast<Word16>(iInput))); }
static BURGER_INLINE Int32 Load(Int32 iInput) { return static_cast<Int32>(Load(static_cast<Word32>(iInput))); }
static BURGER_INLINE Int64 Load(Int64 iInput) { return static_cast<Int64>(Load(static_cast<Word64>(iInput))); }
#if (!defined(BURGER_PS2) && !defined(BURGER_64BITCPU)) || defined(DOXYGEN)
static BURGER_INLINE Word Load(Word uInput) { return static_cast<Word>(Load(static_cast<Word32>(uInput))); }
static BURGER_INLINE Int Load(Int iInput) { return static_cast<Int>(Load(static_cast<Word32>(iInput))); }
static BURGER_INLINE Word Load(const Word *pInput) { return static_cast<Word>(Load(reinterpret_cast<const Word32*>(pInput))); }
static BURGER_INLINE Int Load(const Int *pInput) { return static_cast<Int>(Load(reinterpret_cast<const Word32*>(pInput))); }
static BURGER_INLINE void Store(Word *pOutput,Word uInput) { Store(reinterpret_cast<Word32*>(pOutput),static_cast<Word32>(uInput)); }
static BURGER_INLINE void Store(Int *pOutput,Int iInput) { Store(reinterpret_cast<Word32*>(pOutput),static_cast<Word32>(iInput)); }
static BURGER_INLINE Word LoadAny(const Word *pInput) { return static_cast<Word>(LoadAny(reinterpret_cast<const Word32*>(pInput))); }
static BURGER_INLINE Int LoadAny(const Int *pInput) { return static_cast<Int>(LoadAny(reinterpret_cast<const Word32*>(pInput))); }
static BURGER_INLINE void StoreAny(Word *pOutput,Word uInput) { StoreAny(reinterpret_cast<Word32*>(pOutput),static_cast<Word32>(uInput)); }
static BURGER_INLINE void StoreAny(Int *pOutput,Int iInput) { StoreAny(reinterpret_cast<Word32*>(pOutput),static_cast<Word32>(iInput)); }
static BURGER_INLINE void Fixup(Word *pInput) { Fixup(reinterpret_cast<Word32*>(pInput)); }
static BURGER_INLINE void Fixup(Int *pInput) { Fixup(reinterpret_cast<Word32*>(pInput)); }
static BURGER_INLINE void FixupAny(Word *pInput) { FixupAny(reinterpret_cast<Word32*>(pInput)); }
static BURGER_INLINE void FixupAny(Int *pInput) { FixupAny(reinterpret_cast<Word32*>(pInput)); }
#endif
static BURGER_INLINE Int16 Load(const Int16 *pInput) { return static_cast<Int16>(Load(reinterpret_cast<const Word16*>(pInput))); }
static BURGER_INLINE Int32 Load(const Int32 *pInput) { return static_cast<Int32>(Load(reinterpret_cast<const Word32*>(pInput))); }
static BURGER_INLINE Int64 Load(const Int64 *pInput) { return static_cast<Int64>(Load(reinterpret_cast<const Word64*>(pInput))); }
static BURGER_INLINE void Store(Int16 *pOutput,Int16 iInput) { Store(reinterpret_cast<Word16*>(pOutput),static_cast<Word16>(iInput)); }
static BURGER_INLINE void Store(Int32 *pOutput,Int32 iInput) { Store(reinterpret_cast<Word32*>(pOutput),static_cast<Word32>(iInput)); }
static BURGER_INLINE void Store(Int64 *pOutput,Int64 iInput) { Store(reinterpret_cast<Word64*>(pOutput),static_cast<Word64>(iInput)); }
static BURGER_INLINE Int16 LoadAny(const Int16 *pInput) { return static_cast<Int16>(LoadAny(reinterpret_cast<const Word16*>(pInput))); }
static BURGER_INLINE Int32 LoadAny(const Int32 *pInput) { return static_cast<Int32>(LoadAny(reinterpret_cast<const Word32*>(pInput))); }
static BURGER_INLINE Int64 LoadAny(const Int64 *pInput) { return static_cast<Int64>(LoadAny(reinterpret_cast<const Word64*>(pInput))); }
static BURGER_INLINE void StoreAny(Int16 *pOutput,Int16 iInput) { StoreAny(reinterpret_cast<Word16*>(pOutput),static_cast<Word16>(iInput)); }
static BURGER_INLINE void StoreAny(Int32 *pOutput,Int32 iInput) { StoreAny(reinterpret_cast<Word32*>(pOutput),static_cast<Word32>(iInput)); }
static BURGER_INLINE void StoreAny(Int64 *pOutput,Int64 iInput) { StoreAny(reinterpret_cast<Word64*>(pOutput),static_cast<Word64>(iInput)); }
static BURGER_INLINE void Fixup(Int16 *pInput) { Fixup(reinterpret_cast<Word16*>(pInput)); }
static BURGER_INLINE void Fixup(Int32 *pInput) { Fixup(reinterpret_cast<Word32*>(pInput)); }
static BURGER_INLINE void Fixup(Int64 *pInput) { Fixup(reinterpret_cast<Word64*>(pInput)); }
static BURGER_INLINE void Fixup(float *pInput) { Fixup(reinterpret_cast<Word32*>(pInput)); }
static BURGER_INLINE void Fixup(double *pInput) { Fixup(reinterpret_cast<Word64*>(pInput)); }
static BURGER_INLINE void FixupAny(Int16 *pInput) { FixupAny(reinterpret_cast<Word16*>(pInput)); }
static BURGER_INLINE void FixupAny(Int32 *pInput) { FixupAny(reinterpret_cast<Word32*>(pInput)); }
static BURGER_INLINE void FixupAny(Int64 *pInput) { FixupAny(reinterpret_cast<Word64*>(pInput)); }
static BURGER_INLINE void FixupAny(float *pInput) { FixupAny(reinterpret_cast<Word32*>(pInput)); }
static BURGER_INLINE void FixupAny(double *pInput) { FixupAny(reinterpret_cast<Word64*>(pInput)); }
};
class NativeEndian {
public:
static Word16 BURGER_INLINE Load(Word16 uInput) { return uInput; }
static Word32 BURGER_INLINE Load(Word32 uInput) { return uInput; }
static Word64 BURGER_INLINE Load(Word64 uInput) { return uInput; }
static float BURGER_INLINE Load(float fInput) { return fInput; }
static double BURGER_INLINE Load(double dInput) { return dInput; }
static Word16 BURGER_INLINE Load(const Word16 *pInput) { return pInput[0]; }
static Word32 BURGER_INLINE Load(const Word32 *pInput) { return pInput[0]; }
static Word64 BURGER_INLINE Load(const Word64 *pInput) { return pInput[0]; }
static float BURGER_INLINE Load(const float *pInput) { return pInput[0]; }
static double BURGER_INLINE Load(const double *pInput) { return pInput[0]; }
static void BURGER_INLINE Store(Word16 *pOutput,Word16 uInput) { pOutput[0] = uInput; }
static void BURGER_INLINE Store(Word32 *pOutput,Word32 uInput) { pOutput[0] = uInput; }
static void BURGER_INLINE Store(Word64 *pOutput,Word64 uInput) { pOutput[0] = uInput; }
static void BURGER_INLINE Store(float *pOutput,float fInput) { pOutput[0] = fInput; }
static void BURGER_INLINE Store(double *pOutput,double dInput) { pOutput[0] = dInput; }
#if defined(BURGER_WATCOM)
static Word16 BURGER_INLINE LoadAny(const Word16 *pInput) { return BurgerNativeEndianLoadAny16(pInput); }
static Word32 BURGER_INLINE LoadAny(const Word32 *pInput) { return BurgerNativeEndianLoadAny32(pInput); }
#else
static Word16 BURGER_API LoadAny(const Word16 *pInput);
static Word32 BURGER_API LoadAny(const Word32 *pInput);
#endif
static Word64 BURGER_API LoadAny(const Word64 *pInput);
static float BURGER_API LoadAny(const float *pInput);
static double BURGER_API LoadAny(const double *pInput);
static void BURGER_API StoreAny(Word16 *pOutput,Word16 uInput);
static void BURGER_API StoreAny(Word32 *pOutput,Word32 uInput);
static void BURGER_API StoreAny(Word64 *pOutput,Word64 uInput);
static void BURGER_API StoreAny(float *pOutput,float fInput);
static void BURGER_API StoreAny(double *pOutput,double dInput);
static void BURGER_INLINE Fixup(Word16 *) {}
static void BURGER_INLINE Fixup(Word32 *) {}
static void BURGER_INLINE Fixup(Word64 *) {}
static void BURGER_INLINE FixupAny(Word16 *) {}
static void BURGER_INLINE FixupAny(Word32 *) {}
static void BURGER_INLINE FixupAny(Word64 *) {}
static Int16 BURGER_INLINE Load(Int16 iInput) { return iInput; }
static Int32 BURGER_INLINE Load(Int32 iInput) { return iInput; }
static Int64 BURGER_INLINE Load(Int64 iInput) { return iInput; }
#if (!defined(BURGER_PS2) && !defined(BURGER_64BITCPU)) || defined(DOXYGEN)
static Word BURGER_INLINE Load(Word uInput) { return uInput; }
static Int BURGER_INLINE Load(Int iInput) { return iInput; }
static Word BURGER_INLINE Load(const Word *pInput) { return pInput[0]; }
static Int BURGER_INLINE Load(const Int *pInput) { return pInput[0]; }
static void BURGER_INLINE Store(Word *pOutput,Word uInput) { pOutput[0] = uInput; }
static void BURGER_INLINE Store(Int *pOutput,Int iInput) { pOutput[0] = iInput; }
static Word BURGER_INLINE LoadAny(const Word *pInput) { return static_cast<Word>(LoadAny(reinterpret_cast<const Word32*>(pInput))); }
static Int BURGER_INLINE LoadAny(const Int *pInput) { return static_cast<Int>(LoadAny(reinterpret_cast<const Word32*>(pInput))); }
static void BURGER_INLINE StoreAny(Word *pOutput,Word uInput) { StoreAny(reinterpret_cast<Word32*>(pOutput),static_cast<Word32>(uInput)); }
static void BURGER_INLINE StoreAny(Int *pOutput,Int iInput) { StoreAny(reinterpret_cast<Word32*>(pOutput),static_cast<Word32>(iInput)); }
static void BURGER_INLINE Fixup(Word *) {}
static void BURGER_INLINE Fixup(Int *) {}
static void BURGER_INLINE FixupAny(Word *) {}
static void BURGER_INLINE FixupAny(Int *) {}
#endif
static Int16 BURGER_INLINE Load(const Int16 *pInput) { return pInput[0]; }
static Int32 BURGER_INLINE Load(const Int32 *pInput) { return pInput[0]; }
static Int64 BURGER_INLINE Load(const Int64 *pInput) { return pInput[0]; }
static void BURGER_INLINE Store(Int16 *pOutput,Int16 iInput) { pOutput[0] = iInput; }
static void BURGER_INLINE Store(Int32 *pOutput,Int32 iInput) { pOutput[0] = iInput; }
static void BURGER_INLINE Store(Int64 *pOutput,Int64 iInput) { pOutput[0] = iInput; }
static Int16 BURGER_INLINE LoadAny(const Int16 *pInput) { return static_cast<Int16>(LoadAny(reinterpret_cast<const Word16*>(pInput))); }
static Int32 BURGER_INLINE LoadAny(const Int32 *pInput) { return static_cast<Int32>(LoadAny(reinterpret_cast<const Word32*>(pInput))); }
static Int64 BURGER_INLINE LoadAny(const Int64 *pInput) { return static_cast<Int64>(LoadAny(reinterpret_cast<const Word64*>(pInput))); }
static void BURGER_INLINE StoreAny(Int16 *pOutput,Int16 iInput) { StoreAny(reinterpret_cast<Word16*>(pOutput),static_cast<Word16>(iInput)); }
static void BURGER_INLINE StoreAny(Int32 *pOutput,Int32 iInput) { StoreAny(reinterpret_cast<Word32*>(pOutput),static_cast<Word32>(iInput)); }
static void BURGER_INLINE StoreAny(Int64 *pOutput,Int64 iInput) { StoreAny(reinterpret_cast<Word64*>(pOutput),static_cast<Word64>(iInput)); }
static void BURGER_INLINE Fixup(Int16 *) {}
static void BURGER_INLINE Fixup(Int32 *) {}
static void BURGER_INLINE Fixup(Int64 *) {}
static void BURGER_INLINE Fixup(float *) {}
static void BURGER_INLINE Fixup(double *) {}
static void BURGER_INLINE FixupAny(Int16 *) {}
static void BURGER_INLINE FixupAny(Int32 *) {}
static void BURGER_INLINE FixupAny(Int64 *) {}
static void BURGER_INLINE FixupAny(float *) {}
static void BURGER_INLINE FixupAny(double *) {}
};
#if defined(BURGER_LITTLEENDIAN)
class LittleEndian : public NativeEndian {};
class BigEndian : public SwapEndian {};
#else
class LittleEndian : public SwapEndian {};
class BigEndian : public NativeEndian {};
#endif
}
namespace Burger {
struct StaticRTTI {
	const char* m_pClassName;		///< Pointer to the name of the class
	const StaticRTTI* m_pParent;	///< Pointer to the parent in a derived class
	BURGER_INLINE const char* GetClassName(void) const { return m_pClassName; }
	Word BURGER_API IsInList(const StaticRTTI *pInput) const;
};
}
#define BURGER_RTTI_IN_CLASS() \
public: virtual const Burger::StaticRTTI* GetStaticRTTI(void) const; \
	static const Burger::StaticRTTI g_StaticRTTI
#define BURGER_RTTI_IN_BASE_CLASS() \
public: BURGER_INLINE const char* GetClassName(void) const { return GetStaticRTTI()->GetClassName(); } \
	BURGER_RTTI_IN_CLASS()
#define BURGER_CREATE_STATICRTTI_BASE(__ClassName) \
	const Burger::StaticRTTI* __ClassName::GetStaticRTTI(void) const { return &g_StaticRTTI; } \
	const Burger::StaticRTTI __ClassName::g_StaticRTTI = {#__ClassName,NULL}
#define BURGER_CREATE_STATICRTTI_PARENT(__ClassName,__ParentClass) \
	const Burger::StaticRTTI * __ClassName ::GetStaticRTTI(void) const { return &g_StaticRTTI; } \
	const Burger::StaticRTTI __ClassName::g_StaticRTTI = {#__ClassName,&__ParentClass::g_StaticRTTI }
#define BURGER_STATICRTTI_ISTYPE(__ClassName,__Pointer) (__Pointer)->GetStaticRTTI()->IsInList(&__ClassName::g_StaticRTTI)
#define BURGER_RTTICAST(__ClassName,__Pointer) ((__Pointer) && ((__Pointer)->GetStaticRTTI()->IsInList(&__ClassName::g_StaticRTTI)) ? static_cast<__ClassName*>(__Pointer) : NULL)
#define BURGER_RTTICONSTCAST(__ClassName,__Pointer) ((__Pointer) && ((__Pointer)->GetStaticRTTI()->IsInList(&__ClassName::g_StaticRTTI)) ? static_cast<const __ClassName*>(__Pointer) : NULL)
namespace Burger {
class Base {
	BURGER_RTTI_IN_BASE_CLASS();
public:
	virtual ~Base();
};
}
namespace Burger {
extern void BURGER_API PrintHexDigit(Word uInput);
extern void BURGER_API PrintHex(Word8 uInput);
extern void BURGER_API PrintHex(Word16 uInput);
extern void BURGER_API PrintHex(Word32 uInput);
extern void BURGER_API PrintHex(Word64 uInput);
}
#ifdef __cplusplus
extern "C" {
#endif
#if !defined(GUID_DEFINED) || defined(DOXYGEN)
#if !defined(DOXYGEN)
#define GUID_DEFINED		// Define used by the windows headers
#endif
typedef struct _GUID {
	Word32 Data1;			///< Initial 32 bits as a little endian Word32
	Word16 Data2;			///< Next 16 bits as a little endian Word16
	Word16 Data3;			///< Third value as a 16 bit little endian Word16
	Word8 Data4[8];			///< Remaining 64 bits as 8 bytes
} GUID;
#endif
#ifdef __cplusplus
}
#endif
namespace Burger {
extern const GUID g_GUIDZero;		///< Empty GUID
extern void BURGER_API GUIDInit(GUID *pOutput);
extern void BURGER_API GUIDToString(char *pOutput,const GUID *pInput);
extern Word BURGER_API GUIDFromString(GUID *pOutput,const char *pInput);
extern Word BURGER_API GUIDHash(const GUID *pInput);
extern Word BURGER_API GUIDIsEqual(const GUID *pInput1,const GUID *pInput2);
extern int BURGER_API GUIDCompare(const GUID *pInput1,const GUID *pInput2);
}
namespace Burger {
class ISOLatin1 {
public:
	enum {BAD=-1};
	static const Word8 BURGER_ALIGN(UpperCaseTable[256],16);
	static const Word8 BURGER_ALIGN(LowerCaseTable[256],16);
	static const Word8 BURGER_ALIGN(ToUTF8Table[128][4],16);
	static Word BURGER_API FromUTF8(const char *pInput);
	static Word BURGER_API FromUTF8(char *pOutput,WordPtr uOutputSize,const char *pInput);
	static Word BURGER_API FromUTF8(char *pOutput,WordPtr uOutputSize,const char *pInput,WordPtr uInputSize);
};
}
namespace Burger {
class MacRomanUS {
public:
	enum {BAD=-1};
	static const Word8 BURGER_ALIGN(UpperCaseTable[256],16);
	static const Word8 BURGER_ALIGN(LowerCaseTable[256],16);
	static const Word8 BURGER_ALIGN(ToUTF8Table[128][4],16);
	static Word BURGER_API FromUTF8(const char *pInput);
	static Word BURGER_API FromUTF8(char *pOutput,WordPtr uOutputSize,const char *pInput);
	static Word BURGER_API FromUTF8(char *pOutput,WordPtr uOutputSize,const char *pInput,WordPtr uInputSize);
};
}
namespace Burger {
class Win1252 {
public:
	enum {BAD=-1};
	static const Word8 BURGER_ALIGN(UpperCaseTable[256],16);
	static const Word8 BURGER_ALIGN(LowerCaseTable[256],16);
	static const Word8 BURGER_ALIGN(ToUTF8Table[128][4],16);
	static Word BURGER_API FromUTF8(const char *pInput);
	static Word BURGER_API FromUTF8(char *pOutput,WordPtr uOutputSize,const char *pInput);
	static Word BURGER_API FromUTF8(char *pOutput,WordPtr uOutputSize,const char *pInput,WordPtr uInputSize);
};
}
namespace Burger {
#if defined(BURGER_PS3)
	BURGER_INLINE Word32 AtomicSwap(volatile Word32 *pOutput,Word32 uInput) { Word32 uTemp; do { uTemp = __builtin_lwarx(pOutput,0); } while(__builtin_stwcx(uInput,pOutput,0)==0); return uTemp; }
	BURGER_INLINE Word32 AtomicPreIncrement(volatile Word32 *pInput) { Word32 uTemp; do { uTemp = __builtin_lwarx(pInput,0)+1; } while(__builtin_stwcx(uTemp,pInput,0)==0); return uTemp; }
	BURGER_INLINE Word32 AtomicPostIncrement(volatile Word32 *pInput) { Word32 uTemp; do { uTemp = __builtin_lwarx(pInput,0); } while(__builtin_stwcx(uTemp+1,pInput,0)==0); return uTemp; }
	BURGER_INLINE Word32 AtomicPreDecrement(volatile Word32 *pInput) { Word32 uTemp; do { uTemp = __builtin_lwarx(pInput,0)-1; } while(__builtin_stwcx(uTemp,pInput,0)==0); return uTemp; }
	BURGER_INLINE Word32 AtomicPostDecrement(volatile Word32 *pInput) { Word32 uTemp; do { uTemp = __builtin_lwarx(pInput,0); } while(__builtin_stwcx(uTemp-1,pInput,0)==0); return uTemp; }
	BURGER_INLINE Word32 AtomicAdd(volatile Word32 *pInput,Word32 uValue) { Word32 uTemp; do { uTemp = __builtin_lwarx(pInput,0); } while(__builtin_stwcx(uTemp+uValue,pInput,0)==0); return uTemp; }
	BURGER_INLINE Word32 AtomicSubtract(volatile Word32 *pInput,Word32 uValue) { Word32 uTemp; do { uTemp = __builtin_lwarx(pInput,0); } while(__builtin_stwcx(uTemp-uValue,pInput,0)==0); return uTemp; }
	BURGER_INLINE Word AtomicSetIfMatch(volatile Word32 *pInput,Word32 uBefore,Word32 uAfter) { Word uResult; do { Word32 uTemp = __builtin_lwarx(pInput,0); uResult = (uTemp == uBefore); if (!uResult) break; } while(__builtin_stwcx(uAfter,pInput,0)==0); return uResult; }
	BURGER_INLINE Word32 AtomicSwap(volatile Word64 *pOutput,Word64 uInput) { Word64 uTemp; do { uTemp = __builtin_ldarx(pOutput,0); } while(__builtin_stdcx(uInput,pOutput,0)==0); return uTemp; }
	BURGER_INLINE Word32 AtomicPreIncrement(volatile Word64 *pInput) { Word64 uTemp; do { uTemp = __builtin_ldarx(pInput,0)+1; } while(__builtin_stdcx(uTemp,pInput,0)==0); return uTemp; }
	BURGER_INLINE Word32 AtomicPostIncrement(volatile Word64 *pInput) { Word64 uTemp; do { uTemp = __builtin_ldarx(pInput,0); } while(__builtin_stdcx(uTemp+1,pInput,0)==0); return uTemp; }
	BURGER_INLINE Word32 AtomicPreDecrement(volatile Word64 *pInput) { Word64 uTemp; do { uTemp = __builtin_ldarx(pInput,0)-1; } while(__builtin_stdcx(uTemp,pInput,0)==0); return uTemp; }
	BURGER_INLINE Word32 AtomicPostDecrement(volatile Word64 *pInput) { Word64 uTemp; do { uTemp = __builtin_ldarx(pInput,0); } while(__builtin_stdcx(uTemp-1,pInput,0)==0); return uTemp; }
	BURGER_INLINE Word32 AtomicAdd(volatile Word64 *pInput,Word64 uValue) { Word64 uTemp; do { uTemp = __builtin_ldarx(pInput,0); } while(__builtin_stdcx(uTemp+uValue,pInput,0)==0); return uTemp; }
	BURGER_INLINE Word32 AtomicSubtract(volatile Word64 *pInput,Word64 uValue) { Word64 uTemp; do { uTemp = __builtin_ldarx(pInput,0); } while(__builtin_stdcx(uTemp-uValue,pInput,0)==0); return uTemp; }
	BURGER_INLINE Word AtomicSetIfMatch(volatile Word64 *pInput,Word64 uBefore,Word64 uAfter) { Word uResult; do { Word64 uTemp = __builtin_ldarx(pInput,0); uResult = (uTemp == uBefore); if (!uResult) break; } while(__builtin_stdcx(uAfter,pInput,0)==0); return uResult; }
#elif defined(BURGER_ANDROID) || defined(BURGER_PS4) || defined(BURGER_PSP2) || defined(BURGER_MACOSX) || defined(BURGER_IOS)
	BURGER_INLINE Word32 AtomicSwap(volatile Word32 *pOutput,Word32 uInput) { Word32 uTemp; do { uTemp = pOutput[0]; } while(__sync_val_compare_and_swap(pOutput,uTemp,uInput)!=uTemp); return uTemp;}
	BURGER_INLINE Word32 AtomicPreIncrement(volatile Word32 *pInput) { return __sync_add_and_fetch(pInput,1); }
	BURGER_INLINE Word32 AtomicPostIncrement(volatile Word32 *pInput) { return __sync_fetch_and_add(pInput,1); }
#if defined(BURGER_POWERPC) && defined(BURGER_MACOSX)	// Hack to get around a compiler crash for Xcode 3.1.4 for PowerPC!!!
	BURGER_INLINE Word32 AtomicPreDecrement(volatile Word32 *pInput) { return __sync_add_and_fetch(pInput,0xFFFFFFFFU); }
#else
	BURGER_INLINE Word32 AtomicPreDecrement(volatile Word32 *pInput) { return __sync_sub_and_fetch(pInput,1); }
#endif
	BURGER_INLINE Word32 AtomicPostDecrement(volatile Word32 *pInput) { return __sync_fetch_and_sub(pInput,1); }
	BURGER_INLINE Word32 AtomicAdd(volatile Word32 *pInput,Word32 uValue) { return __sync_fetch_and_add(pInput,uValue); }
	BURGER_INLINE Word32 AtomicSubtract(volatile Word32 *pInput,Word32 uValue) { return __sync_fetch_and_sub(pInput,uValue); }
	BURGER_INLINE Word AtomicSetIfMatch(volatile Word32 *pInput,Word32 uBefore,Word32 uAfter) { return __sync_bool_compare_and_swap(pInput,uAfter,uBefore); }
	BURGER_INLINE Word64 AtomicSwap(volatile Word64 *pOutput,Word64 uInput) { Word64 uTemp; do { uTemp = pOutput[0]; } while(__sync_val_compare_and_swap(pOutput,uTemp,uInput)!=uTemp); return uTemp;}
	BURGER_INLINE Word64 AtomicPreIncrement(volatile Word64 *pInput) { return __sync_add_and_fetch(pInput,1); }
	BURGER_INLINE Word64 AtomicPostIncrement(volatile Word64 *pInput) { return __sync_fetch_and_add(pInput,1); }
	BURGER_INLINE Word64 AtomicPreDecrement(volatile Word64 *pInput) { return __sync_sub_and_fetch(pInput,1); }
	BURGER_INLINE Word64 AtomicPostDecrement(volatile Word64 *pInput) { return __sync_fetch_and_sub(pInput,1); }
	BURGER_INLINE Word64 AtomicAdd(volatile Word64 *pInput,Word64 uValue) { return __sync_fetch_and_add(pInput,uValue); }
	BURGER_INLINE Word64 AtomicSubtract(volatile Word64 *pInput,Word64 uValue) { return __sync_fetch_and_sub(pInput,uValue); }
	BURGER_INLINE Word AtomicSetIfMatch(volatile Word64 *pInput,Word64 uBefore,Word64 uAfter) { return __sync_bool_compare_and_swap(pInput,uAfter,uBefore); }
#elif defined(BURGER_XBOX360) || defined(BURGER_WINDOWS) || defined(BURGER_MSDOS)
	BURGER_INLINE Word32 AtomicSwap(volatile Word32 *pOutput,Word32 uInput) { return static_cast<Word32>(_InterlockedExchange(reinterpret_cast<volatile long *>(pOutput),static_cast<long>(uInput)));}
	BURGER_INLINE Word32 AtomicPreIncrement(volatile Word32 *pInput) { return static_cast<Word32>(_InterlockedIncrement(reinterpret_cast<volatile long *>(pInput))); }
	BURGER_INLINE Word32 AtomicPostIncrement(volatile Word32 *pInput) { return static_cast<Word32>(_InterlockedIncrement(reinterpret_cast<volatile long *>(pInput))-1); }
	BURGER_INLINE Word32 AtomicPreDecrement(volatile Word32 *pInput) { return static_cast<Word32>(_InterlockedDecrement(reinterpret_cast<volatile long *>(pInput))); }
	BURGER_INLINE Word32 AtomicPostDecrement(volatile Word32 *pInput) { return static_cast<Word32>(_InterlockedDecrement(reinterpret_cast<volatile long *>(pInput))+1); }
	BURGER_INLINE Word32 AtomicAdd(volatile Word32 *pInput,Word32 uValue) { return static_cast<Word32>(_InterlockedExchangeAdd(reinterpret_cast<volatile long *>(pInput),static_cast<long>(uValue))); }
	BURGER_INLINE Word32 AtomicSubtract(volatile Word32 *pInput,Word32 uValue) { return static_cast<Word32>(_InterlockedExchangeAdd(reinterpret_cast<volatile long *>(pInput),-static_cast<long>(uValue))); }
	BURGER_INLINE Word AtomicSetIfMatch(volatile Word32 *pInput,Word32 uBefore,Word32 uAfter) { return _InterlockedCompareExchange(reinterpret_cast<volatile long *>(pInput),static_cast<long>(uAfter),static_cast<long>(uBefore))==static_cast<long>(uBefore); }
#if defined(BURGER_64BITCPU)
	BURGER_INLINE Word64 AtomicSwap(volatile Word64 *pOutput,Word64 uInput) { return _InterlockedExchange64(reinterpret_cast<volatile __int64 *>(pOutput),uInput); }
	BURGER_INLINE Word64 AtomicPreIncrement(volatile Word64 *pInput) { return _InterlockedIncrement64(reinterpret_cast<volatile __int64 *>(pInput)); }
	BURGER_INLINE Word64 AtomicPostIncrement(volatile Word64 *pInput) { return _InterlockedIncrement64(reinterpret_cast<volatile __int64 *>(pInput))-1; }
	BURGER_INLINE Word64 AtomicPreDecrement(volatile Word64 *pInput) { return _InterlockedDecrement64(reinterpret_cast<volatile __int64 *>(pInput)); }
	BURGER_INLINE Word64 AtomicPostDecrement(volatile Word64 *pInput) { return _InterlockedDecrement64(reinterpret_cast<volatile __int64 *>(pInput))+1; }
	BURGER_INLINE Word64 AtomicAdd(volatile Word32 *pInput,Word64 uValue) { return _InterlockedExchangeAdd64(reinterpret_cast<volatile __int64 *>(pInput),uValue); }
	BURGER_INLINE Word64 AtomicSubtract(volatile Word64 *pInput,Word64 uValue) { return _InterlockedExchangeAdd64(reinterpret_cast<volatile __int64 *>(pInput),0-uValue); }
	BURGER_INLINE Word AtomicSetIfMatch(volatile Word64 *pInput,Word64 uBefore,Word64 uAfter) { return _InterlockedCompareExchange64(reinterpret_cast<volatile __int64 *>(pInput),uAfter,uBefore)==static_cast<__int64>(uBefore); }
#endif
#else
	BURGER_INLINE Word32 AtomicSwap(volatile Word32 *pOutput,Word32 uInput) { Word32 uTemp = pOutput[0]; pOutput[0] = uInput; return uTemp; }
	BURGER_INLINE Word32 AtomicPreIncrement(volatile Word32 *pInput) { Word32 uTemp = pInput[0]+1; pInput[0] = uTemp; return uTemp; }
	BURGER_INLINE Word32 AtomicPostIncrement(volatile Word32 *pInput) { Word32 uTemp = pInput[0]; pInput[0] = uTemp+1; return uTemp; }
	BURGER_INLINE Word32 AtomicPreDecrement(volatile Word32 *pInput) { Word32 uTemp = pInput[0]-1; pInput[0] = uTemp; return uTemp; }
	BURGER_INLINE Word32 AtomicPostDecrement(volatile Word32 *pInput) { Word32 uTemp = pInput[0]; pInput[0] = uTemp-1; return uTemp; }
	BURGER_INLINE Word32 AtomicAdd(volatile Word32 *pInput,Word32 uValue) { Word32 uTemp = pInput[0]; pInput[0] = uTemp+uValue; return uTemp; }
	BURGER_INLINE Word32 AtomicSubtract(volatile Word32 *pInput,Word32 uValue) { Word32 uTemp = pInput[0]; pInput[0] = uTemp-uValue; return uTemp; }
	BURGER_INLINE Word AtomicSetIfMatch(volatile Word32 *pInput,Word32 uBefore,Word32 uAfter) { Word uTemp = pInput[0]==uBefore; if (uTemp) { pInput[0] = uAfter; } return uTemp; }
#if defined(BURGER_64BITCPU) || defined(DOXYGEN)
	BURGER_INLINE Word64 AtomicSwap(volatile Word64 *pOutput,Word64 uInput) { Word64 uTemp = pOutput[0]; pOutput[0] = uInput; return uTemp; }
	BURGER_INLINE Word64 AtomicPreIncrement(volatile Word64 *pInput) { Word64 uTemp = pInput[0]+1; pInput[0] = uTemp; return uTemp; }
	BURGER_INLINE Word64 AtomicPostIncrement(volatile Word64 *pInput) { Word64 uTemp = pInput[0]; pInput[0] = uTemp+1; return uTemp; }
	BURGER_INLINE Word64 AtomicPreDecrement(volatile Word64 *pInput) { Word64 uTemp = pInput[0]-1; pInput[0] = uTemp; return uTemp; }
	BURGER_INLINE Word64 AtomicPostDecrement(volatile Word64 *pInput) { Word64 uTemp = pInput[0]; pInput[0] = uTemp-1; return uTemp; }
	BURGER_INLINE Word64 AtomicAdd(volatile Word64 *pInput,Word64 uValue) { Word64 uTemp = pInput[0]; pInput[0] = uTemp+uValue; return uTemp; }
	BURGER_INLINE Word64 AtomicSubtract(volatile Word64 *pInput,Word64 uValue) { Word64 uTemp = pInput[0]; pInput[0] = uTemp-uValue; return uTemp; }
	BURGER_INLINE Word AtomicSetIfMatch(volatile Word64 *pInput,Word64 uBefore,Word64 uAfter) { Word uTemp = pInput[0]==uBefore; if (uTemp) { pInput[0] = uAfter; } return uTemp; }
#endif
#endif
}
namespace Burger {
class CriticalSection {
	BURGER_DISABLECOPYCONSTRUCTORS(CriticalSection);
#if defined(BURGER_WINDOWS) || defined(BURGER_XBOX360) || defined(DOXYGEN)
	CRITICAL_SECTION m_Lock;	///< Critical section for OS calls (Windows and Xbox 360 only)
#endif
#if defined(BURGER_PS3) || defined(DOXYGEN)
	sys_lwmutex_t m_Lock;		///< Critical section for PS3 (PS3 only)
#endif
#if defined(BURGER_PS4) || defined(DOXYGEN)
	pthread_mutex *m_Lock;		///< Critical section for PS4 (PS4 only)
#endif
#if (defined(BURGER_SHIELD) || defined(BURGER_MACOSX) || defined(BURGER_IOS)) || defined(DOXYGEN)
	friend class ConditionVariable;
	pthread_mutex_t m_Lock;		///< Critical section for Android/MacOSX/iOS (Android/MacOSX/iOS only)
#endif
#if defined(BURGER_VITA) || defined(DOXYGEN)
	int m_iLock;				///< Critical section ID for VITA
#endif
public:
	CriticalSection();
	~CriticalSection();
	void Lock(void);
	Word TryLock(void);
	void Unlock(void);
};
class CriticalSectionStatic : public CriticalSection {
	Word m_bValid;			///< Set to \ref TRUE when constructed
public:
	CriticalSectionStatic();
	~CriticalSectionStatic();
	BURGER_INLINE void Lock(void) {	if (m_bValid) { CriticalSection::Lock(); }}
	BURGER_INLINE Word TryLock(void) { if (m_bValid) { return CriticalSection::TryLock(); } return FALSE; }
	BURGER_INLINE void Unlock(void) { if (m_bValid) { CriticalSection::Unlock(); }}
};
class CriticalSectionLock {
	BURGER_DISABLECOPYCONSTRUCTORS(CriticalSectionLock);
	CriticalSection *m_pCriticalSection;			///< Pointer to the lock held
public:
	CriticalSectionLock(CriticalSection *pCriticalSection) :
		m_pCriticalSection(pCriticalSection) { m_pCriticalSection->Lock(); }
	~CriticalSectionLock() { m_pCriticalSection->Unlock(); }
};
<<<<<<< HEAD
class Semaphore {
#if (defined(BURGER_WINDOWS) || defined(BURGER_XBOX360)) || defined(DOXYGEN)
	void *m_pSemaphore;			///< Semaphore HANDLE (Windows only)
=======
}
#if defined(BURGER_PS4)
extern "C" float fabsf(float);
extern "C" double fabs(double);
extern "C" float sqrtf(float);
extern "C" double sqrt(double);
#elif defined(BURGER_MACOSX) || (defined(BURGER_IOS) && (defined(BURGER_X86) || defined(BURGER_AMD64)))
extern "C" float sqrtf(float);
extern "C" double sqrt(double);
#if !defined(BURGER_METROWERKS)
extern "C" float fabsf(float);
extern "C" double fabs(double);
>>>>>>> 8cfb6bc... Updated makeprojects to auto-generate iOS projects under XCode 5.x. iOS binaries are "fat", meaning they have armv7, armv7s, arm64, i386 and x86_64 binaries so it works both on a native device and on the simulators
#endif
#if (defined(BURGER_SHIELD)) || defined(DOXYGEN)
	sem_t m_Semaphore;			///< Semaphore instance (Android)
	Word m_bInitialized;		///< \ref TRUE if the semaphore instance successfully initialized
#endif
#if defined(BURGER_VITA) || defined(DOXYGEN)
	int m_iSemaphore;				///< Semaphore ID for VITA
#endif
#if (defined(BURGER_MACOSX) || defined(BURGER_IOS)) || defined(DOXYGEN)
	semaphore_t m_Semaphore;	///< Semaphore instance (MacOSX/iOS only)
	task_t m_Owner;				///< Task ID of the semaphore owner (MacOSX/iOS only)
	Word m_bInitialized;		///< \ref TRUE if the semaphore instance successfully initialized
#endif
	volatile Word32 m_uCount;	///< Semaphore count value
public:
	Semaphore(Word32 uCount=0);
	~Semaphore();
	BURGER_INLINE Word Acquire(void) { return TryAcquire(BURGER_MAXUINT); }
	Word BURGER_API TryAcquire(Word uMilliseconds=0);
	Word BURGER_API Release(void);
	BURGER_INLINE Word32 GetValue(void) const { return m_uCount; }
};
class ConditionVariable {
#if (defined(BURGER_SHIELD) || defined(BURGER_MACOSX) || defined(BURGER_IOS)) || defined(DOXYGEN)
	pthread_cond_t m_ConditionVariable;	///< Condition variable instance (Android/MacOSX/iOS only)
	Word m_bInitialized;			///< \ref TRUE if the Condition variable instance successfully initialized (Android/MacOSX/iOS only)
#endif
#if (defined(BURGER_VITA)) || defined(DOXYGEN)
	int m_iConditionVariable;	///< Condition variable instance (Vita only)
	int m_iMutex;				///< Mutex for the condition variable (Vita only)
#endif
#if !(defined(BURGER_SHIELD) || defined(BURGER_MACOSX) || defined(BURGER_IOS)) || defined(DOXYGEN)
	CriticalSection m_CriticalSection;	///< CriticalSection for this class (Non-specialized platforms)
	Semaphore m_WaitSemaphore;		///< Binary semaphore for forcing thread to wait for a signal (Non-specialized platforms)
	Semaphore m_SignalsSemaphore;	///< Binary semaphore for the number of pending signals (Non-specialized platforms)
	Word32 m_uWaiting;				///< Count of waiting threads (Non-specialized platforms)
	Word32 m_uSignals;				///< Count of signals to be processed (Non-specialized platforms)
#endif
public:
	ConditionVariable();
	~ConditionVariable();
	Word BURGER_API Signal(void);
	Word BURGER_API Broadcast(void);
	Word BURGER_API Wait(CriticalSection *pCriticalSection,Word uMilliseconds=BURGER_MAXUINT);
};
class Thread {
public:
	typedef WordPtr (BURGER_API *FunctionPtr)(void *pThis);		///< Thread entry prototype
private:
	FunctionPtr m_pFunction;		///< Pointer to the thread
	void *m_pData;					///< Data pointer for the thread
	Semaphore *m_pSemaphore;		///< Temp Semaphore for synchronization
#if (defined(BURGER_WINDOWS) || defined(BURGER_XBOX360)) || defined(DOXYGEN)
	void *m_pThreadHandle;			///< HANDLE to the thread (Windows/Xbox 360 only)
	Word32 m_uThreadID;				///< System ID of the thread (Windows/Xbox 360 only)
#endif
#if (defined(BURGER_MACOSX) || defined(BURGER_IOS)) || defined(DOXYGEN)
	struct _opaque_pthread_t *m_pThreadHandle;	///< Pointer to the thread data (MacOSX/iOS only)
#endif
#if (defined(BURGER_VITA)) || defined(DOXYGEN)
	int m_iThreadID;				///< System ID of the thread (Vita only)
#endif
	WordPtr m_uResult;				///< Result code of the thread on exit
public:
	Thread();
	Thread(FunctionPtr pFunction,void *pData);
	~Thread();
	Word BURGER_API Start(FunctionPtr pFunction,void *pData);
	Word BURGER_API Wait(void);
	Word BURGER_API Kill(void);
	static void BURGER_API Run(void *pThis);
	BURGER_INLINE WordPtr GetResult(void) const { return m_uResult; }
#if (defined(BURGER_WINDOWS) || defined(BURGER_XBOX360) || defined(BURGER_MACOSX) || defined(BURGER_IOS)) || defined(DOXYGEN)
	BURGER_INLINE Word IsInitialized(void) const { return m_pThreadHandle!=NULL; }
#elif defined(BURGER_VITA)
	BURGER_INLINE Word IsInitialized(void) const { return m_iThreadID>=0; }
#else
	BURGER_INLINE Word IsInitialized(void) const { return FALSE; }
#endif
};
}
namespace Burger {
struct MemoryManager {
	typedef void *(BURGER_API *ProcAlloc)(MemoryManager *pThis,WordPtr uSize);		///< Function prototype for allocating memory
	typedef void (BURGER_API *ProcFree)(MemoryManager *pThis,const void *pInput);	///< Function prototype for releasing memory
	typedef void *(BURGER_API *ProcRealloc)(MemoryManager *pThis,const void *pInput,WordPtr uSize);	///< Function prototype for reallocating memory.
	typedef void (BURGER_API *ProcShutdown)(MemoryManager *pThis);					///< Function prototype for destructor
	ProcAlloc m_pAlloc;			///< Pointer to allocation function
	ProcFree m_pFree;			///< Pointer to memory release function
	ProcRealloc m_pRealloc;		///< Pointer to the memory reallocation function
	ProcShutdown m_pShutdown;	///< Pointer to the shutdown function
	BURGER_INLINE void *Alloc(WordPtr uSize) { return m_pAlloc(this,uSize); }
	BURGER_INLINE void Free(const void *pInput) { return m_pFree(this,pInput); }
	BURGER_INLINE void *Realloc(const void *pInput,WordPtr uSize) { return m_pRealloc(this,pInput,uSize); }
	BURGER_INLINE void Shutdown(void) { m_pShutdown(this); }
	void * BURGER_API AllocClear(WordPtr uSize);
	static void BURGER_API Shutdown(MemoryManager *pThis);
	static void * BURGER_API AllocSystemMemory(WordPtr uSize);
	static void BURGER_API FreeSystemMemory(const void *pInput);
};
}
namespace Burger {
class MemoryManagerANSI : public MemoryManager {
	BURGER_DISABLECOPYCONSTRUCTORS(MemoryManagerANSI);
public:
	MemoryManagerANSI();
	BURGER_INLINE void *Alloc(WordPtr uSize) { return Alloc(this,uSize); }
	BURGER_INLINE void Free(const void *pInput) { return Free(this,pInput); }
	BURGER_INLINE void *Realloc(const void *pInput,WordPtr uSize)  { return Realloc(this,pInput,uSize); }
private:
	static void *BURGER_API Alloc(MemoryManager *pThis,WordPtr uSize);
	static void BURGER_API Free(MemoryManager *pThis,const void *pInput);
	static void *BURGER_API Realloc(MemoryManager *pThis,const void *pInput,WordPtr uSize);
};
class MemoryManagerGlobalANSI : public MemoryManagerANSI {
	BURGER_DISABLECOPYCONSTRUCTORS(MemoryManagerGlobalANSI);
	MemoryManager *m_pPrevious;			///< Pointer to the previous memory manager
public:
	MemoryManagerGlobalANSI();
	~MemoryManagerGlobalANSI();
};
}
namespace Burger {
class MemoryManagerHandle : public MemoryManager {
	BURGER_DISABLECOPYCONSTRUCTORS(MemoryManagerHandle);
public:
	enum {
		LOCKED=0x80,		///< Lock flag
		FIXED=0x40,			///< Set if memory is fixed (High memory)
		MALLOC=0x20,		///< Memory was Malloc'd
		INUSE=0x10,			///< Set if handle is used
		PURGABLE=0x01,		///< Set if handle is purgeable
		DEFAULTHANDLECOUNT=500,	///< Starting number of handles
		DEFAULTMEMORYCHUNK=0x1000000,	///< Default memory to allocate
		DEFAULTMINIMUMRESERVE=0x40000,	///< Default minimum free system memory
		MEMORYIDUNUSED=0xFFFDU,			///< Free handle ID
		MEMORYIDFREE=0xFFFEU,			///< Internal free memory ID
		MEMORYIDRESERVED=0xFFFFU,		///< Immutable handle ID
#if defined(BURGER_MSDOS) || defined(BURGER_DS) || defined(BURGER_68K)
		ALIGNMENT=4			///< Default memory alignment
#else
		ALIGNMENT=16		///< Default memory alignment
#endif
	};
	enum eMemoryStage {
		StageCompact,		///< Garbage collection stage to compact memory
		StagePurge,			///< Garbage collection stage to purge purgeable memory
		StageHailMary,		///< Garbage collection stage to purge and then compact memory
		StageGiveup			///< Critical memory stage, release all possibly freeable memory
	};
	typedef void (BURGER_API *MemPurgeProc)(void *pThis,eMemoryStage eStage);	///< Function prototype for user supplied garbage collection subroutine
private:
	struct Handle_t {
		void *m_pData;				///< Pointer to true memory (Must be the first entry!)
		WordPtr m_uLength;			///< Length of allocated memory
		Handle_t *m_pNextHandle;	///< Next handle in the chain
		Handle_t *m_pPrevHandle;	///< Previous handle in the chain
		Handle_t *m_pNextPurge;		///< Next handle in purge list
		Handle_t *m_pPrevPurge;		///< Previous handle in the purge list
		Word m_uFlags;				///< Memory flags or parent used handle
		Word m_uID;					///< Memory ID
	};
	struct SystemBlock_t {
		SystemBlock_t *m_pNext;		///< Next block in the chain
	};
	SystemBlock_t *m_pSystemMemoryBlocks;	///< Linked list of memory blocks taken from the system
	MemPurgeProc m_MemPurgeCallBack;	///< Callback before memory purging
	void *m_pMemPurge;					///< User pointer for memory purge
	WordPtr m_uTotalAllocatedMemory;	///< All of the memory currently allocated
	WordPtr m_uTotalSystemMemory;		///< Total allocated system memory
	Handle_t *m_pFreeHandle;			///< Pointer to the free handle list
	Word m_uTotalHandleCount;			///< Number of handles allocated
	Handle_t m_LowestUsedMemory;	///< First used memory handle (Start of linked list)
	Handle_t m_HighestUsedMemory;	///< Last used memory handle (End of linked list)
	Handle_t m_FreeMemoryChunks;	///< Free handle list
	Handle_t m_PurgeHands;			///< Purged handle list
	Handle_t m_PurgeHandleFiFo;		///< Purged handle linked list
	CriticalSection m_Lock;			///< Lock for multithreading support
	static void *BURGER_API AllocProc(MemoryManager *pThis,WordPtr uSize);
	static void BURGER_API FreeProc(MemoryManager *pThis,const void *pInput);
	static void *BURGER_API ReallocProc(MemoryManager *pThis,const void *pInput,WordPtr uSize);
	static void BURGER_API ShutdownProc(MemoryManager *pThis);
	Handle_t *BURGER_API AllocNewHandle(void);
	void BURGER_API GrabMemoryRange(void *pData,WordPtr uLength,Handle_t *pParent,Handle_t *pHandle);
	void BURGER_API ReleaseMemoryRange(void *pData,WordPtr uLength,Handle_t *pParent);
	void BURGER_API PrintHandles(const Handle_t *pFirst,const Handle_t *pLast,Word bNoCheck);
public:
	MemoryManagerHandle(WordPtr uDefaultMemorySize=DEFAULTMEMORYCHUNK,Word uDefaultHandleCount=DEFAULTHANDLECOUNT,WordPtr uMinReserveSize=DEFAULTMINIMUMRESERVE);
	~MemoryManagerHandle();
	BURGER_INLINE WordPtr GetTotalAllocatedMemory(void) const { return m_uTotalAllocatedMemory; }
	BURGER_INLINE void *Alloc(WordPtr uSize) { return AllocProc(this,uSize); }
	BURGER_INLINE void Free(const void *pInput) { return FreeProc(this,pInput); }
	BURGER_INLINE void *Realloc(const void *pInput,WordPtr uSize) { return ReallocProc(this,pInput,uSize); }
	BURGER_INLINE void Shutdown(void) { ShutdownProc(this); }
	void **BURGER_API AllocHandle(WordPtr uSize,Word uFlags=0);
	void BURGER_API FreeHandle(void **ppInput);
	void **BURGER_API ReallocHandle(void **ppInput,WordPtr uSize);
	void **BURGER_API RefreshHandle(void **ppInput);
	void **BURGER_API FindHandle(const void *pInput);
	static WordPtr BURGER_API GetSize(void **ppInput);
	static WordPtr BURGER_API GetSize(const void *pInput);
	WordPtr BURGER_API GetTotalFreeMemory(void);
	static void * BURGER_API Lock(void **ppInput);
	static void BURGER_API Unlock(void **ppInput);
	static void BURGER_API SetID(void **ppInput,Word uID);
	void BURGER_API SetPurgeFlag(void **ppInput,Word uFlag);
	static Word BURGER_API GetLockedState(void **ppInput);
	void BURGER_API SetLockedState(void **ppInput,Word uFlag);
	void BURGER_API Purge(void **ppInput);
	Word BURGER_API PurgeHandles(WordPtr uSize);
	void BURGER_API CompactHandles(void);
	void BURGER_API DumpHandles(void);
};
class MemoryManagerGlobalHandle : public MemoryManagerHandle {
	BURGER_DISABLECOPYCONSTRUCTORS(MemoryManagerGlobalHandle);
	MemoryManager *m_pPrevious;			///< Pointer to the previous memory manager
public:
	MemoryManagerGlobalHandle(WordPtr uDefaultMemorySize=DEFAULTMEMORYCHUNK,Word uDefaultHandleCount=DEFAULTHANDLECOUNT,WordPtr uMinReserveSize=DEFAULTMINIMUMRESERVE);
	~MemoryManagerGlobalHandle();
};
}
namespace Burger {
<<<<<<< HEAD
extern void *BURGER_API Alloc(WordPtr uSize);
extern void *BURGER_API AllocClear(WordPtr uSize);
extern void BURGER_API Free(const void *pInput);
extern void *BURGER_API Realloc(const void *pInput,WordPtr uSize);
extern void *BURGER_API AllocCopy(const void *pInput,WordPtr uSize);
class GlobalMemoryManager {
public:
	static MemoryManager * BURGER_API Init(MemoryManager *pInstance);
	static void BURGER_API Shutdown(MemoryManager *pPrevious=NULL);
	static BURGER_INLINE MemoryManager *GetInstance(void) { return g_pInstance; }
private:
	static MemoryManager *g_pInstance;	///< Pointer to the currently active memory manager
=======
struct FixedMatrix3D_t;
struct Matrix3D_t {
	Vector3D_t x;	///< 32 bit floating point X row for the 3D Matrix
	Vector3D_t y;	///< 32 bit floating point Y row for the 3D Matrix
	Vector3D_t z;	///< 32 bit floating point Z row for the 3D Matrix
	void BURGER_API Zero(void);
	void BURGER_API Identity(void);
	void BURGER_API Set(const Matrix3D_t *pInput);
	void BURGER_API Set(const FixedMatrix3D_t *pInput);
	void BURGER_API SetYaw(float fYaw);
	void BURGER_API SetPitch(float fPitch);
	void BURGER_API SetRoll(float fRoll);
	void BURGER_API SetYXZ(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetYZX(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetXYZ(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetXZY(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetZYX(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetZXY(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetTranslate(float fX,float fY);
	void BURGER_API SetFromQuaternion(const Vector4D_t *pInput);
	void BURGER_API TransposeSetYaw(float fYaw);
	void BURGER_API TransposeSetPitch(float fPitch);
	void BURGER_API TransposeSetRoll(float fRoll);
	void BURGER_API TransposeSetYXZ(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetYZX(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetXYZ(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetXZY(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetZYX(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetZXY(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetFromQuaternion(const Vector4D_t *pInput);
	void BURGER_API Transpose(void);
	void BURGER_API Transpose(const Matrix3D_t *pInput);
	void BURGER_API GetXRow(Vector3D_t *pOutput) const;
	void BURGER_API GetYRow(Vector3D_t *pOutput) const;
	void BURGER_API GetZRow(Vector3D_t *pOutput) const;
	void BURGER_API GetXColumn(Vector3D_t *pOutput) const;
	void BURGER_API GetYColumn(Vector3D_t *pOutput) const;
	void BURGER_API GetZColumn(Vector3D_t *pOutput) const;
	void BURGER_API SetXRow(const Vector3D_t *pInput);
	void BURGER_API SetYRow(const Vector3D_t *pInput);
	void BURGER_API SetZRow(const Vector3D_t *pInput);
	void BURGER_API SetXColumn(const Vector3D_t *pInput);
	void BURGER_API SetYColumn(const Vector3D_t *pInput);
	void BURGER_API SetZColumn(const Vector3D_t *pInput);
	void BURGER_API Multiply(const Matrix3D_t *pInput);
	void BURGER_API Multiply(const Matrix3D_t *pInput1,const Matrix3D_t *pInput2);
	void BURGER_API Multiply(float fScale);
	void BURGER_API Multiply(const Matrix3D_t *pInput,float fScale);
	void BURGER_API Transform(Vector3D_t *pInput) const;
	void BURGER_API Transform(Vector3D_t *pOutput,const Vector3D_t *pInput) const;
	void BURGER_API TransformAdd(Vector3D_t *pInput,const Vector3D_t *pTranslate) const;
	void BURGER_API TransformAdd(Vector3D_t *pOutput,const Vector3D_t *pInput,const Vector3D_t *pTranslate) const;
	void BURGER_API TransposeTransform(Vector3D_t *pInput) const;
	void BURGER_API TransposeTransform(Vector3D_t *pOutput,const Vector3D_t *pInput) const;
	void BURGER_API TransposeTransformAdd(Vector3D_t *pInput,const Vector3D_t *pTranslate) const;
	void BURGER_API TransposeTransformAdd(Vector3D_t *pOutput,const Vector3D_t *pInput,const Vector3D_t *pTranslate) const;
>>>>>>> 8cfb6bc... Updated makeprojects to auto-generate iOS projects under XCode 5.x. iOS binaries are "fat", meaning they have armv7, armv7s, arm64, i386 and x86_64 binaries so it works both on a native device and on the simulators
};
template <class T>
T * BURGER_API New(void) {
	return new (Alloc(sizeof(T))) T();
}
template <class T>
void BURGER_API Delete(const T*pInput) {
	if (pInput) {
		const_cast<T *>(pInput)->~T();
		Free(pInput);
	}
}
}
namespace Burger {
<<<<<<< HEAD
enum {
	ASCII_LOWER=0x01,
	ASCII_UPPER=0x02,
	ASCII_CONTROL=0x04,
	ASCII_SPACE=0x08,
	ASCII_WHITESPACE=0x10,
	ASCII_PUNCTUATION=0x20,
	ASCII_HEX=0x40,
	ASCII_DIGIT=0x80,
	NOENDINGNULL=0x4000,
	LEADINGZEROS=0x8000
};
extern const char g_EmptyString[1];
extern const char g_CRLFString[3];
extern const char g_CRString[2];
extern const char g_LFString[2];
extern const char g_TrueString[5];
extern const char g_FalseString[6];
extern const char g_YesString[4];
extern const char g_NoString[3];
extern const char *g_WeekDays[7];
extern const char *g_Months[12];
extern const Word16 g_EmptyString16[1];
extern const Word16 g_CRLFString16[3];
extern const Word16 g_CRString16[2];
extern const Word16 g_LFString16[2];
extern const Word16 g_TrueString16[5];
extern const Word16 g_FalseString16[6];
extern const Word16 g_YesString16[4];
extern const Word16 g_NoString16[3];
extern const Word8 BURGER_ALIGN(g_AsciiTestTable[128],16);
extern const char BURGER_ALIGN(g_NibbleToAsciiUppercase[16],16);
extern const char BURGER_ALIGN(g_NibbleToAsciiLowercase[16],16);
extern const Word8 BURGER_ALIGN(g_AsciiToWord8Table[256],16);
extern const Word8 BURGER_ALIGN(g_ReverseBits[256],16);
extern const Word32 g_TensTable32[10];
extern const Word64 g_TensTable64[20];
extern Word32 BURGER_API BCDToWord(Word32 uInput);
extern Word32 BURGER_API WordToBCD(Word32 uInput);
extern Word32 BURGER_API PowerOf2(Word32 uInput);
extern Word64 BURGER_API PowerOf2(Word64 uInput);
BURGER_INLINE Word32 ToLower(Word32 uInput) { if (static_cast<Word32>(uInput-'A')<26U) uInput+=32; return uInput;}
BURGER_INLINE Word32 ToUpper(Word32 uInput) { if (static_cast<Word32>(uInput-'a')<26U) uInput-=32; return uInput;}
extern Word32 BURGER_API BitReverse(Word32 uInput,Word uBitLength);
extern Word64 BURGER_API BitReverse(Word64 uInput,Word uBitLength);
extern Word BURGER_API BitSetCount(Word32 uInput);
extern Word BURGER_API BitSetCount(Word64 uInput);
extern void BURGER_API CStringToPString(Word8 *pOutput,const char *pInput);
extern void BURGER_API PStringToCString(char *pOutput,const Word8 *pInput);
extern char * BURGER_API ParseBeyondWhiteSpace(const char *pInput);
extern char * BURGER_API ParseToDelimiter(const char *pInput);
extern char * BURGER_API ParseBeyondEOL(const char *pInput);
extern char * BURGER_API ParseBeyondEOL(const char *pInput,WordPtr uLength);
extern char * BURGER_API ParseQuotedString(char *pOutput,WordPtr uOutputSize,const char *pInput);
extern WordPtr BURGER_API CopyUpToEOL(char *pOutput,WordPtr uOutputSize,const char *pInput,WordPtr uInputSize);
extern void BURGER_API StripLeadingSpaces(char* pInput);
extern void BURGER_API StripTrailingSpaces(char* pInput);
extern void BURGER_API StripLeadingWhiteSpace(char* pInput);
extern void BURGER_API StripTrailingWhiteSpace(char* pInput);
extern void BURGER_API StripLeadingAndTrailingSpaces(char* pInput);
extern void BURGER_API StripLeadingAndTrailingWhiteSpace(char* pInput);
extern void BURGER_API StripAllFromList(char* pInput,const char* pList);
extern void BURGER_API StripAllButList(char* pInput,const char* pList);
extern void BURGER_API StripTrailing(char* pInput, const char* pList);
extern void BURGER_API StripLeading(char* pInput, const char* pList);
extern void BURGER_API RemoveTrailingChar(char *pInput,Word uRemove);
extern void BURGER_API ForceTrailingChar(char *pInput,Word uLast);
extern void BURGER_API SlashesToColons(char *pInput);
extern void BURGER_API SlashesToColons(char *pOutput,const char *pInput);
extern void BURGER_API SlashesToWindowsSlashes(char *pInput);
extern void BURGER_API SlashesToWindowsSlashes(char *pOutput,const char *pInput);
extern void BURGER_API SlashesToLinuxSlashes(char *pInput);
extern void BURGER_API SlashesToLinuxSlashes(char *pOutput,const char *pInput);
extern void BURGER_API Replace(char *pInput,Word uFrom,Word uTo);
extern void BURGER_API Replace(char *pOutput,const char *pInput,Word uFrom,Word uTo);
extern char* BURGER_API GetFileExtension(const char *pInput);
extern void BURGER_API SetFileExtension(char* pInput,const char* pNewExtension);
extern void BURGER_API MemoryCopy(void *pOutput,const void *pInput,WordPtr uCount);
extern void BURGER_API MemoryMove(void *pOutput,const void *pInput,WordPtr uCount);
extern void BURGER_API MemoryClear(void *pOutput,WordPtr uCount);
extern void BURGER_API MemoryFill(void *pOutput,Word8 uFill,WordPtr uCount);
extern void BURGER_API MemoryNot(void *pOutput,WordPtr uCount);
extern void BURGER_API MemoryNot(void *pOutput,const void *pInput,WordPtr uCount);
extern void BURGER_API MemoryXor(void *pOutput,Word8 uXor,WordPtr uCount);
extern void BURGER_API MemoryXor(void *pOutput,const void *pInput,Word8 uXor,WordPtr uCount);
extern void BURGER_API MemoryXor(void *pOutput,const void *pInput,WordPtr uCount);
extern void BURGER_API MemoryXor(void *pOutput,const void *pInput1,const void *pInput2,WordPtr uCount);
extern WordPtr BURGER_API StringLength(const char *pInput);
extern WordPtr BURGER_API StringLength(const Word16 *pInput);
extern void BURGER_API StringCopy(char *pOutput,const char *pInput);
extern void BURGER_API StringCopy(char *pOutput,WordPtr uOutputSize,const char *pInput);
extern void BURGER_API StringCopy(char *pOutput,WordPtr uOutputSize,const char *pInput,WordPtr uInputSize);
extern void BURGER_API StringCopy(Word16 *pOutput,const Word16 *pInput);
extern void BURGER_API StringCopy(Word16 *pOutput,WordPtr uOutputSize,const Word16 *pInput);
extern void BURGER_API StringCopy(Word16 *pOutput,WordPtr uOutputSize,const Word16 *pInput,WordPtr uInputSize);
extern char * BURGER_API StringDuplicate(const char *pInput);
extern char * BURGER_API StringDuplicate(const char *pInput,WordPtr uPadding);
extern void BURGER_API StringDelete(const char *pInput);
extern void BURGER_API StringConcatenate(char *pOutput,const char *pInput);
extern void BURGER_API StringConcatenate(char *pOutput,WordPtr uOutputSize,const char *pInput);
extern void BURGER_API StringConcatenate(char *pOutput,WordPtr uOutputSize,const char *pInput,WordPtr uInputSize);
extern void BURGER_API StringConcatenate(Word16 *pOutput,const Word16 *pInput);
extern void BURGER_API StringConcatenate(Word16 *pOutput,WordPtr uOutputSize,const Word16 *pInput);
extern int BURGER_API StringCompare(const char *pInput1,const char *pInput2);
extern int BURGER_API StringCompare(const char *pInput1,const char *pInput2,WordPtr uMaxLength);
extern int BURGER_API StringCompare(const Word16 *pInput1,const Word16 *pInput2);
extern int BURGER_API StringCompare(const Word16 *pInput1,const Word16 *pInput2,WordPtr uMaxLength);
extern int BURGER_API StringCaseCompare(const char *pInput1,const char *pInput2);
extern int BURGER_API StringCaseCompare(const char *pInput1,const char *pInput2,WordPtr uMaxLength);
extern int BURGER_API MemoryCompare(const void *pInput1,const void *pInput2,WordPtr uCount);
extern int BURGER_API MemoryCaseCompare(const void *pInput1,const void *pInput2,WordPtr uCount);
extern Word BURGER_API Wildcardcmp(const char *pInput,const char *pWildcard);
extern Word BURGER_API HasWildcard(const char *pInput);
extern void BURGER_API StringUppercase(char *pInput);
extern void BURGER_API StringUppercase(char *pOutput,const char *pInput);
extern void BURGER_API StringLowercase(char *pInput);
extern void BURGER_API StringLowercase(char *pOutput,const char *pInput);
extern char * BURGER_API StringCharacter(const char *pInput,int iChar);
extern Word16 * BURGER_API StringCharacter(const Word16 *pInput,Word uChar);
extern char * BURGER_API MemoryCharacter(const char *pInput,WordPtr uInputSize,int iChar);
extern Word16 * BURGER_API MemoryCharacter(const Word16 *pInput,WordPtr uInputSize,Word uChar);
extern char * BURGER_API StringCharacterReverse(const char *pInput,int iChar);
extern Word16 * BURGER_API StringCharacterReverse(const Word16 *pInput,Word uChar);
extern char * BURGER_API MemoryCharacterReverse(const char *pInput,WordPtr uInputSize,int iChar);
extern Word16 * BURGER_API MemoryCharacterReverse(const Word16 *pInput,WordPtr uInputSize,Word uChar);
extern char * BURGER_API StringString(const char *pInput,const char *pTest);
extern char * BURGER_API StringCaseString(const char *pInput,const char *pTest);
extern char * BURGER_API NumberToAsciiHex(char *pOutput,Word32 uInput,Word uDigits=0);
extern char * BURGER_API NumberToAsciiHex(char *pOutput,Word64 uInput,Word uDigits=0);
extern char * BURGER_API NumberToAscii(char *pOutput,Word32 uInput,Word uDigits=0);
extern char * BURGER_API NumberToAscii(char *pOutput,Int32 iInput,Word uDigits=0);
extern char * BURGER_API NumberToAscii(char *pOutput,Word64 uInput,Word uDigits=0);
extern char * BURGER_API NumberToAscii(char *pOutput,Int64 iInput,Word uDigits=0);
extern char * BURGER_API NumberToAscii(char *pOutput,float fInput);
extern char * BURGER_API NumberToAscii(char *pOutput,double dInput);
extern Word32 BURGER_API AsciiToInteger(const char *pInput,const char **pDest=NULL);
extern float BURGER_API AsciiToFloat(const char *pInput,const char **pDest=NULL);
extern double BURGER_API AsciiToDouble(const char *pInput,const char **pDest=NULL);
extern Word BURGER_API AsciiToBoolean(const char *pInput,const char **pDest=NULL);
extern Word BURGER_API AsciiToWord(const char *pInput,Word uDefault,Word uMin=0,Word uMax=BURGER_MAXUINT);
extern Int BURGER_API AsciiToInteger(const char *pInput,Int iDefault,Int iMin=(-BURGER_MAXINT)-1,Int iMax=BURGER_MAXINT);
extern Word BURGER_API AsciiToInteger(Word32 *pOutput,const char *pInput);
extern Word BURGER_API AsciiToBoolean(const char *pInput,Word bDefault);
extern Word BURGER_API AsciiToBoolean(Word *pOutput,const char *pInput);
extern float BURGER_API AsciiToFloat(const char *pInput,float fDefault);
extern float BURGER_API AsciiToFloat(const char *pInput,float fDefault,float fMin,float fMax);
extern Word BURGER_API AsciiToFloat(float *pOutput,const char *pInput);
extern double BURGER_API AsciiToDouble(const char *pInput,double dDefault);
extern double BURGER_API AsciiToDouble(const char *pInput,double dDefault,double dMin,double dMax);
extern Word BURGER_API AsciiToDouble(double *pOutput,const char *pInput);
}
namespace Burger {
class UTF8 {
public:
	enum {BAD=-1};
	static const Word8 BURGER_ALIGN(TokenSizeTable[256],16);
	static const Word8 ByteOrderMark[3];
	static Word BURGER_API IsValidSingle(const char *pInput);
	static Word BURGER_API IsValid(const char *pInput);
	static Word BURGER_API IsValid(const char *pInput,WordPtr uInputSize);
	static WordPtr BURGER_API GetTokenSize(const char *pInput);
	static const char * BURGER_API NextToken(const char *pInput);
	static WordPtr BURGER_API FromMacRomanUS(char *pOutput,Word uInput);
	static WordPtr BURGER_API FromMacRomanUS(char *pOutput,WordPtr uOutputSize,const char *pInput);
	static WordPtr BURGER_API FromMacRomanUS(char *pOutput,WordPtr uOutputSize,const char *pInput,WordPtr uInputSize);
	static WordPtr BURGER_API FromWin1252(char *pOutput,Word uInput);
	static WordPtr BURGER_API FromWin1252(char *pOutput,WordPtr uOutputSize,const char *pInput);
	static WordPtr BURGER_API FromWin1252(char *pOutput,WordPtr uOutputSize,const char *pInput,WordPtr uInputSize);
	static WordPtr BURGER_API FromISOLatin1(char *pOutput,Word uInput);
	static WordPtr BURGER_API FromISOLatin1(char *pOutput,WordPtr uOutputSize,const char *pInput);
	static WordPtr BURGER_API FromISOLatin1(char *pOutput,WordPtr uOutputSize,const char *pInput,WordPtr uInputSize);
	static WordPtr BURGER_API FromGeneric(char *pOutput,const Word8 pTranslateTable[128][4],Word uInput);
	static WordPtr BURGER_API FromGeneric(char *pOutput,WordPtr uOutputSize,const Word8 pTranslateTable[128][4],const char *pInput);
	static WordPtr BURGER_API FromGeneric(char *pOutput,WordPtr uOutputSize,const Word8 pTranslateTable[128][4],const char *pInput,WordPtr uInputSize);
	static WordPtr BURGER_API FromUTF16(char *pOutput,Word16 uInput);
	static WordPtr BURGER_API FromUTF16(char *pOutput,WordPtr uOutputSize,const Word16 *pInput);
	static WordPtr BURGER_API FromUTF16(char *pOutput,WordPtr uOutputSize,const Word16 *pInput,WordPtr uInputSize);
	static char * BURGER_API FromUTF16(const Word16 *pInput);
	static WordPtr BURGER_API FromUTF32(char *pOutput,Word32 uInput);
	static WordPtr BURGER_API FromUTF32(char *pOutput,WordPtr uOutputSize,const Word32 *pInput);
	static WordPtr BURGER_API FromUTF32(char *pOutput,WordPtr uOutputSize,const Word32 *pInput,WordPtr uInputSize);
	static Word BURGER_API ToGeneric(const char *pInput,const Word8 pTranslateTable[128][4]);
	static WordPtr BURGER_API ToGeneric(char *pOutput,WordPtr uOutputSize,const Word8 pTranslateTable[128][4],const char *pInput);
	static WordPtr BURGER_API ToGeneric(char *pOutput,WordPtr uOutputSize,const Word8 pTranslateTable[128][4],const char *pInput,WordPtr uInputSize);
};
}
namespace Burger {
class UTF16 {
public:
	enum {BAD=-1,ENDIANMARK=0xFEFF,
#if defined(BURGER_LITTLEENDIAN)
	BE=0xFFFE,LE=0xFEFF};
#else
	BE=0xFEFF,LE=0xFFFE};
#endif
	static const Word16 BURGER_ALIGN(FromMacRomanUSTable[128],16);
	static const Word16 BURGER_ALIGN(FromWin1252Table[128],16);
	static const Word16 BURGER_ALIGN(FromISOLatin1Table[128],16);
	static Word BURGER_API IsValid(Word16 uInput);
	static Word BURGER_API IsValid(const Word16 *pInput);
	static Word BURGER_API IsValid(const Word16 *pInput,WordPtr uInputSize);
	static Word32 BURGER_API FromUTF8(const char *pInput);
	static WordPtr BURGER_API FromUTF8(Word16 *pOutput,WordPtr uOutputSize,const char *pInput);
	static WordPtr BURGER_API FromUTF8(Word16 *pOutput,WordPtr uOutputSize,const char *pInput,WordPtr uInputSize);
};
}
namespace Burger {
class UTF32 {
public:
	enum {BAD=-1,ENDIANMARK=0xFEFF,
#if defined(BURGER_LITTLEENDIAN)
	BE=0xFFFE0000,LE=0xFEFF};
#else
	BE=0xFEFF,LE=0xFFFE0000};
#endif
	static Word BURGER_API IsValid(Word32 uInput);
	static Word BURGER_API IsValid(const Word32 *pInput);
	static Word BURGER_API IsValid(const Word32 *pInput,WordPtr uInputSize);
	static Word32 BURGER_API FromUTF8(const char *pInput);
	static Word32 BURGER_API FromUTF8(const char **ppInput);
	static WordPtr BURGER_API FromUTF8(Word32 *pOutput,WordPtr uOutputSize,const char *pInput);
	static WordPtr BURGER_API FromUTF8(Word32 *pOutput,WordPtr uOutputSize,const char *pInput,WordPtr uInputSize);
};
}
namespace Burger {
template<class T>
class Queue {
	struct Element {
		T m_Data;				///< Copy of the data attached to this entry
		Element* m_pNext;		///< Pointer to the next element in the singly linked list
		Element(const T& rData) : m_Data(rData), m_pNext(NULL) { }
	};
	Element* m_pFirstElement;	///< Pointer to the first element in the linked list
	Element* m_pLastElement;	///< Pointer to the last element in the linked list
	WordPtr m_uCount;			///< Number of entries in the linked list
public:
	Queue() : m_pFirstElement(NULL),m_pLastElement(NULL),m_uCount(0) {}
	~Queue()
	{
		clear();
	}
	void clear(void)
	{
		Element *pElement = m_pFirstElement;
		if (pElement) {
			do {
				Element *pNext = pElement->m_pNext;
				Delete(pElement);
				pElement = pNext;
			} while (pElement);
		}
		m_pFirstElement = NULL;
		m_pLastElement = NULL;
		m_uCount = 0;
	}
	BURGER_INLINE const T& back(void) const { return m_pLastElement->m_Data; }
	BURGER_INLINE T& back(void) { return m_pLastElement->m_Data; }
	BURGER_INLINE const T& front(void) const { return m_pFirstElement->m_Data; }
	BURGER_INLINE T& front(void) { return m_pFirstElement->m_Data; }
	void pop(void) {
		Element *pElement = m_pFirstElement;
		m_pFirstElement = pElement->m_pNext;
		Delete(pElement);
		--m_uCount;
		if (m_pLastElement == pElement) {
			m_pLastElement = NULL;
			BURGER_ASSERT((!m_pFirstElement) && (!m_uCount));
		}
	}
	void push(const T& rData) {
		Element *pElement = new (Alloc(sizeof(Element))) Element(rData);
		if (!m_pLastElement) {
			BURGER_ASSERT((!m_pFirstElement) && (!m_uCount));
			m_pLastElement = pElement;
			m_pFirstElement = pElement;
		} else {
			BURGER_ASSERT(!m_pLastElement->m_pNext);
			m_pLastElement->m_pNext = pElement;
			m_pLastElement = pElement;
		}
		++m_uCount;
	}
	BURGER_INLINE WordPtr size(void) const { return m_uCount; }
	BURGER_INLINE Word empty(void) const { return (m_uCount==0); }
};
}
namespace Burger {
class ProxyReferenceCounter {
	BURGER_DISABLECOPYCONSTRUCTORS(ProxyReferenceCounter);
	Word m_uRefCount;				///< Number of weak pointers that are using this object as an anchor
	Word m_bParentAlive;			///< \ref TRUE if the parent object was deleted
	ProxyReferenceCounter() : m_uRefCount(0),m_bParentAlive(TRUE) {}
public:
	static ProxyReferenceCounter *New(void);
	BURGER_INLINE Word IsParentAlive(void) const { return m_bParentAlive; }
	BURGER_INLINE void ParentIsDead(void) { m_bParentAlive = FALSE; }
	BURGER_INLINE void AddRef(void) { ++m_uRefCount; }
	BURGER_INLINE void Release(void) { if (--m_uRefCount == 0) { Free(this); } }
};
class ReferenceCounter : public Base {
	BURGER_DISABLECOPYCONSTRUCTORS(ReferenceCounter);
	Word m_uRefCount;					///< Number of smart pointers that are claiming ownership of this object
	BURGER_RTTI_IN_CLASS();
public:
	ReferenceCounter() : m_uRefCount(0) { }
	virtual ~ReferenceCounter();
	BURGER_INLINE void AddRef(void) { ++m_uRefCount; }
	BURGER_INLINE void Release(void) { if (--m_uRefCount == 0) { Delete(this); } }
};
class WeakPointerAnchor {
	mutable ProxyReferenceCounter* m_pReferenceCounter;
public:
	WeakPointerAnchor() : m_pReferenceCounter(NULL) {}
	~WeakPointerAnchor();
	ProxyReferenceCounter* GetProxyReferenceCounter(void) const;
};
#define BURGER_ALLOW_WEAK_POINTERS() \
public: BURGER_INLINE ProxyReferenceCounter* GetProxyReferenceCounter(void) const { return m_WeakPointerAnchor.GetProxyReferenceCounter(); } \
private: WeakPointerAnchor m_WeakPointerAnchor
class WeakAndStrongBase : public ReferenceCounter {
	BURGER_ALLOW_WEAK_POINTERS();
	BURGER_RTTI_IN_CLASS();
};
template<class T>
class SmartPointer {
	T* m_pData;			///< Private copy of the pointer this class is tracking
	BURGER_INLINE void Replace(T* pData) {
		T* pOld = m_pData;
		if (pData != pOld) {
			if (pData) {
				pData->AddRef();
			}
			if (pOld) {
				pOld->Release();
			}
			m_pData = pData;
		}
	}
public:
	SmartPointer(T* pData) : m_pData(pData)
	{
		if (pData) {
			pData->AddRef();
		}
	}
	SmartPointer() : m_pData(NULL) {}
	SmartPointer(const SmartPointer<T>& rData) : m_pData(rData.m_pData)
	{
		if (m_pData) {
			m_pData->AddRef();
		}
	}
	~SmartPointer() {
		if (m_pData) {
			m_pData->Release();
			m_pData = NULL;
		}
	}
	BURGER_INLINE void operator=(const SmartPointer<T>& rData) { Replace(rData.m_pData); }
	BURGER_INLINE void operator=(T* pData) { Replace(pData); }
	BURGER_INLINE T* operator->() const { return m_pData; }
	BURGER_INLINE T& operator*() const { return *m_pData; }
	BURGER_INLINE operator T*() const { return m_pData; }
	BURGER_INLINE T* GetPtr() const { return m_pData; }
	BURGER_INLINE Word operator==(const SmartPointer<T>& rData) const { return m_pData == rData.m_pData; }
	BURGER_INLINE Word operator!=(const SmartPointer<T>& rData) const { return m_pData != rData.m_pData; }
	BURGER_INLINE Word operator==(const T* pData) const { return m_pData == pData; }
	BURGER_INLINE Word operator!=(const T* pData) const { return m_pData != pData; }
};
template<class T>
class WeakPointer {
	mutable T* m_pData;			///< Pointer to the object being tracked
	mutable SmartPointer<ProxyReferenceCounter> m_pProxy;	///< Pointer to the object the tracked object will notify if it's deleted
	BURGER_INLINE T* Dereference(void) const
	{
		T* pData = m_pData;
		if (pData) {
			if (!m_pProxy->IsParentAlive()) {
				pData = NULL;
				m_pProxy = NULL;
				m_pData = NULL;
			}
		}
		return pData;
	}
public:
	WeakPointer() : m_pData(NULL),m_pProxy() { }
	WeakPointer(T* pData) : m_pData(pData),m_pProxy() {
		if (pData) {
			m_pProxy = pData->GetProxyReferenceCounter();
		}
	}
	WeakPointer(const WeakPointer<T>& rData) : m_pData(rData.GetPtr()),m_pProxy() {
		if (m_pData) {
			m_pProxy = m_pData->GetProxyReferenceCounter();
		}
	}
	WeakPointer(const SmartPointer<T>& rData) : m_pData(rData.GetPtr()),m_pProxy() {
		if (m_pData) {
			m_pProxy = m_pData->GetProxyReferenceCounter();
		}
	}
	~WeakPointer() {}
	BURGER_INLINE void operator=(T* pData)
	{
		m_pData = pData;
		ProxyReferenceCounter *pProxy;
		if (!pData) {
			pProxy = NULL;
		} else {
			pProxy = pData->GetProxyReferenceCounter();
		}
		m_pProxy = pProxy;
	}
	BURGER_INLINE void operator=(const SmartPointer<T>& rData) { operator=(rData.GetPtr()); }
	BURGER_INLINE T* operator->() const { return Dereference(); }
	BURGER_INLINE T* GetPtr() const {	return Dereference(); }
	BURGER_INLINE operator SmartPointer<T>() { return SmartPointer<T>(Dereference()); }
	BURGER_INLINE Word operator==(const T* pData) const { return Dereference() == pData; }
	BURGER_INLINE Word operator!=(const T* pData) const { return Dereference() != pData; }
	BURGER_INLINE Word operator==(const T* pData) { return Dereference() == pData; }
	BURGER_INLINE Word operator!=(const T* pData) { return Dereference() != pData; }
	BURGER_INLINE Word operator==(const SmartPointer<T>& rData) const { return Dereference() == rData.GetPtr(); }
	BURGER_INLINE Word operator!=(const SmartPointer<T>& rData) const { return Dereference() != rData.GetPtr(); }
	BURGER_INLINE Word operator==(const SmartPointer<T>& rData) { return Dereference() == rData.GetPtr(); }
	BURGER_INLINE Word operator!=(const SmartPointer<T>& rData) { return Dereference() != rData.GetPtr(); }
	BURGER_INLINE Word operator==(const WeakPointer<T>& rData) const { return Dereference() == rData.Dereference(); }
	BURGER_INLINE Word operator!=(const WeakPointer<T>& rData) const { return Dereference() != rData.Dereference(); }
};
}
namespace Burger {
template<class T1,class T2>
class Pair {
public:
	T1 first;		///< First object in the pair
	T2 second;		///< Second object in the pair
	Pair() {}
	Pair(const T1 &rFirst,const T2 &rSecond) :
		first(rFirst),
		second(rSecond)
	{
	}
	Pair(const Pair<T1,T2> &rInput) :
		first(rInput.first),
		second(rInput.second)
	{
	}
	void operator=(const Pair<T1,T2> &rInput) {
		first=rInput.first;
		second=rInput.second;
	}
	typedef T1 first_type;
	typedef T2 second_type;
};
}
namespace Burger {
class SimpleArrayBase {
protected:
	void *m_pData;			///< Pointer to the array of class instances
	WordPtr m_uSize;		///< Number of active elements in the array
	WordPtr m_uBufferSize;	///< Maximum number of elements in the array
	WordPtr m_uChunkSize;	///< Size in bytes for each individual element in the array
public:
	SimpleArrayBase(WordPtr uChunkSize) :
		m_pData(NULL),
		m_uSize(0),
		m_uBufferSize(0),
		m_uChunkSize(uChunkSize)
	{}
	SimpleArrayBase(WordPtr uDefault,WordPtr uChunkSize);
	SimpleArrayBase(const SimpleArrayBase &rData);
	~SimpleArrayBase();
	SimpleArrayBase &operator=(const SimpleArrayBase &rData);
	void BURGER_API clear(void);
	void BURGER_API remove_at(WordPtr uIndex);
	void BURGER_API resize(WordPtr uNewSize);
	void BURGER_API reserve(WordPtr uNewBufferSize);
protected:
	void BURGER_API append(const void *pData,WordPtr uCount);
};
template<class T>
class SimpleArray : public SimpleArrayBase {
public:
	SimpleArray() : SimpleArrayBase(sizeof(T)) {}
	SimpleArray(WordPtr uDefault) : SimpleArrayBase(uDefault,sizeof(T)) {}
	BURGER_INLINE T *GetPtr(void) { return static_cast<T *>(m_pData); }
	BURGER_INLINE const T *GetPtr(void) const { return static_cast<const T *>(m_pData); }
	BURGER_INLINE T& operator[](WordPtr uIndex) { BURGER_ASSERT(uIndex < m_uSize); return static_cast<T *>(m_pData)[uIndex]; }
	BURGER_INLINE const T& operator[](WordPtr uIndex) const { BURGER_ASSERT(uIndex < m_uSize); return static_cast<const T *>(m_pData)[uIndex]; }
	BURGER_INLINE WordPtr capacity(void) const { return m_uBufferSize; }
	BURGER_INLINE static WordPtr max_size(void) { return (256*1024*1024) / sizeof(T); }
	BURGER_INLINE WordPtr size(void) const { return m_uSize; }
	BURGER_INLINE Word empty(void) const { return !m_uSize; }
	BURGER_INLINE T& front(void) { return static_cast<T *>(m_pData)[0]; }
	BURGER_INLINE const T& front(void) const { return static_cast<const T *>(m_pData)[0]; }
	BURGER_INLINE T& back(void) { return static_cast<T *>(m_pData)[m_uSize-1]; }
	BURGER_INLINE const T& back(void) const { return static_cast<const T *>(m_pData)[m_uSize-1]; }
	BURGER_INLINE void push_back(T rData) {
		WordPtr uSize = m_uSize;
		WordPtr uBufferSize = m_uBufferSize;
		if (uSize>=uBufferSize) {
			++uBufferSize;
			reserve(uBufferSize + (uBufferSize>>1U));
		}
		static_cast<T *>(m_pData)[uSize] = rData;
		m_uSize = uSize+1U;
	}
	BURGER_INLINE void pop_back(void) {
		BURGER_ASSERT(m_uSize);
		--m_uSize;
	}
	BURGER_INLINE SimpleArray<T>& operator=(const SimpleArray<T>& rData) {
		return static_cast<SimpleArray<T>&>(SimpleArrayBase::operator=(rData));
	}
	BURGER_INLINE void insert_at(WordPtr uIndex,T rData = T())
	{
		WordPtr uSize = m_uSize;
		BURGER_ASSERT(uIndex <= uSize);
		resize(uSize + 1);		// resize adjusts m_uSize to uSize+1
		if (uIndex < uSize) {
			MemoryMove(static_cast<T *>(m_pData)+uIndex+1,static_cast<const T *>(m_pData)+uIndex,sizeof(T) * (uSize - uIndex));
		}
		static_cast<T *>(m_pData)[uIndex] = rData;
	}
	BURGER_INLINE Word remove(T rData) {
		WordPtr uSize = m_uSize;
		Word bResult = FALSE;
		if (uSize) {
			const T *pWork = static_cast<const T *>(m_pData);
			do {
				if (pWork[0] == rData) {
					remove_at(m_uSize-uSize);
					bResult = TRUE;
					break;
				}
				++pWork;
			} while (--uSize);
		}
		return bResult;
	}
	BURGER_INLINE void append(const T *pSourceData,WordPtr uCount) {
		SimpleArrayBase::append(pSourceData,uCount);
	}
	BURGER_INLINE void append(const SimpleArray<T> &rData) {
		SimpleArrayBase::append(rData.m_pData,rData.m_uSize);
	}
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef T value_type;
	BURGER_INLINE iterator begin(void) { return static_cast<T *>(m_pData); }
	BURGER_INLINE iterator end(void) { return static_cast<T *>(m_pData) + m_uSize; }
	BURGER_INLINE const_iterator begin(void) const { return static_cast<const T *>(m_pData); }
	BURGER_INLINE const_iterator end(void) const { return static_cast<const T *>(m_pData) + m_uSize; }
	BURGER_INLINE const_iterator cbegin(void) const { return static_cast<const T *>(m_pData); }
	BURGER_INLINE const_iterator cend(void) const { return static_cast<const T *>(m_pData) + m_uSize; }
	BURGER_INLINE void erase(const_iterator it) {
		WordPtr uIndex = it-static_cast<const T *>(m_pData);
		remove_at(uIndex);
	}
};
}
namespace Burger {
template<class T>
class ClassArray {
	T *m_pData;				///< Pointer to the array of class instances
	WordPtr m_uSize;		///< Number of active elements in the array
	WordPtr m_uBufferSize;	///< Maximum number of elements in the array
	static void Destroy(T* pData,WordPtr uCount) {
		do {
			pData->~T();
			++pData;
		} while (--uCount);
	}
	static void Init(T* pData,WordPtr uCount) {
		do {
			new (pData) T();
			++pData;
		} while (--uCount);
	}
	static void Init(T* pData,WordPtr uCount,const T*pSource)
	{
		do {
			new (pData) T(pSource[0]);
			++pSource;
			++pData;
		} while (--uCount);
	}
	static void Copy(T* pData,WordPtr uCount,const T*pSource) {
		IntPtr iStep = 1;
		if (pData>pSource) {
			iStep = -1;
			pData+=uCount-1;
			pSource+=uCount-1;
		}
		do {
			pData[0] = pSource[0];
			pSource+=iStep;
			pData+=iStep;
		} while (--uCount);
	}
public:
	ClassArray() : m_pData(NULL), m_uSize(0), m_uBufferSize(0) {}
	ClassArray(WordPtr uDefault) : m_pData(NULL),m_uSize(uDefault),m_uBufferSize(uDefault) {
		if (uDefault) {
			T *pData = static_cast<T*>(Alloc(sizeof(T) * uDefault));
			BURGER_ASSERT(pData);
			m_pData = pData;
			Init(pData,uDefault);
		}
	}
	ClassArray(const ClassArray<T>& rData) : m_pData(NULL),m_uSize(rData.size()),m_uBufferSize(rData.size())
	{
		WordPtr uCount = m_uSize;
		if (uCount) {
			T *pData = static_cast<T*>(Alloc(sizeof(T) * uCount));
			m_pData = pData;
			Init(pData,uCount,rData.m_pData);
		}
	}
	~ClassArray() {
		clear();
	}
	BURGER_INLINE T *GetPtr(void) { return m_pData; }
	BURGER_INLINE const T *GetPtr(void) const { return m_pData; }
	BURGER_INLINE T &operator[](WordPtr uIndex) { BURGER_ASSERT(uIndex < m_uSize); return m_pData[uIndex]; }
	BURGER_INLINE const T &operator[](WordPtr uIndex) const { BURGER_ASSERT(uIndex < m_uSize); return m_pData[uIndex]; }
	BURGER_INLINE WordPtr capacity(void) const { return m_uBufferSize; }
	BURGER_INLINE static WordPtr max_size(void) { return (256*1024*1024) / sizeof(T); }
	BURGER_INLINE WordPtr size(void) const { return m_uSize; }
	BURGER_INLINE Word empty(void) const { return m_uSize==0; }
	BURGER_INLINE T& front(void) { return m_pData[0]; }
	BURGER_INLINE const T& front(void) const { return m_pData[0]; }
	BURGER_INLINE T& back(void) { return m_pData[m_uSize-1]; }
	BURGER_INLINE const T & back(void) const { return m_pData[m_uSize-1]; }
	void push_back(const T& rData) {
		WordPtr uSize = m_uSize;
		WordPtr uBufferSize = m_uBufferSize;
		if (uSize>=uBufferSize) {
			++uBufferSize;
			reserve(uBufferSize + (uBufferSize>>1U));
		}
		new (m_pData+uSize) T(rData);
		m_uSize = uSize+1U;
	}
	void pop_back(void) {
		BURGER_ASSERT(m_uSize);
		m_pData[--m_uSize].~T();
	}
	void clear(void) {
		WordPtr uCount = m_uSize;
		if (uCount) {
			Destroy(m_pData,uCount);
		}
		Free(m_pData);
		m_pData = NULL;
		m_uBufferSize = 0;
		m_uSize = 0;
	}
	ClassArray<T>& operator=(const ClassArray<T>& rData) {
		if (&rData!=this) {
			clear();
			WordPtr uCount = rData.size();
			if (uCount) {
				m_uSize = uCount;
				m_uBufferSize = uCount;
				T *pData = static_cast<T*>(Alloc(sizeof(T) * uCount));
				m_pData = pData;
				Init(pData,uCount,rData.m_pData);
			}
		}
		return *this;
	}
	void remove_at(WordPtr uIndex) {
		WordPtr uSize = m_uSize;
		BURGER_ASSERT(uIndex < uSize);
		if (uSize == 1) {
			clear();
		} else {
			WordPtr uCount = (uSize-uIndex)-1;
			if (uCount) {
				Copy(m_pData+uIndex,uCount,m_pData+uIndex+1);
			}
			--uSize;
			m_pData[uSize].~T();	// Destroy the last entry
			m_uSize = uSize;
		}
	}
	void insert_at(WordPtr uIndex,const T & rData = T())
	{
		WordPtr uSize = m_uSize;
		BURGER_ASSERT(uIndex <= uSize);
		resize(uSize + 1);		// resize adjusts m_uSize to uSize+1
		if (uIndex < uSize) {
			Copy(m_pData+uIndex+1,uSize-uIndex,m_pData+uIndex);
		}
		m_pData[uIndex] = rData;
	}
	BURGER_INLINE Word remove(const T &rData) {
		WordPtr uSize = m_uSize;
		Word bResult = FALSE;
		if (uSize) {
			const T *pWork = m_pData;
			do {
				if (*pWork == rData) {
					remove_at(m_uSize-uSize);
					bResult = TRUE;
					break;
				}
				++pWork;
			} while (--uSize);
		}
		return bResult;
	}
	void append(const T *pSourceData,WordPtr uCount) {
		if (uCount) {
			WordPtr uSize = m_uSize;
			resize(uSize + uCount);
			Copy(m_pData+uSize,uCount,pSourceData);
		}
	}
	BURGER_INLINE void append(const ClassArray<T>& rData) { append(rData.m_pData,rData.size()); }
	void resize(WordPtr uNewSize) {
		if (!uNewSize) {
			clear();
		} else {
			WordPtr	uOldSize = m_uSize;
			if (uNewSize<uOldSize) {
				Destroy(m_pData+uNewSize,uOldSize-uNewSize);
				m_uSize = uNewSize;
				uOldSize = uNewSize;
			}
			reserve(uNewSize);
			if (uOldSize<uNewSize) {
				Init(m_pData + uOldSize,uNewSize-uOldSize);
				m_uSize = uNewSize;
			}
		}
	}
	void reserve(WordPtr uNewBufferSize) {
		if (!uNewBufferSize) {
			clear();
		} else {
			WordPtr uSize = m_uSize;
			if (uSize>uNewBufferSize) {
				m_uSize = uNewBufferSize;
				Destroy(m_pData + uNewBufferSize,uSize-uNewBufferSize);
			}
			if (m_uBufferSize!=uNewBufferSize) {
				T *pNewData = static_cast<T*>(Alloc(sizeof(T)*uNewBufferSize));
				BURGER_ASSERT(pNewData);	// need to throw (or something) on malloc failure!
				if (uSize) {
					Init(pNewData,uSize,m_pData);
					Destroy(m_pData,uSize);
				}
				Free(m_pData);
				m_uBufferSize = uNewBufferSize;
				m_pData = pNewData;
			}
		}
	}
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef T value_type;
	BURGER_INLINE iterator begin(void) { return m_pData; }
	BURGER_INLINE iterator end(void) { return m_pData + m_uSize; }
	BURGER_INLINE const_iterator begin(void) const { return m_pData; }
	BURGER_INLINE const_iterator end(void) const { return m_pData + m_uSize; }
	BURGER_INLINE const_iterator cbegin(void) const { return m_pData; }
	BURGER_INLINE const_iterator cend(void) const { return m_pData + m_uSize; }
	BURGER_INLINE void erase(const_iterator it) {
		WordPtr uIndex = it-m_pData;
		remove_at(uIndex);
	}
};
}
namespace Burger {
extern Word BURGER_API CalcAdler16(const void *pInput,WordPtr uInputLength,Word uAdler16=1);
}
namespace Burger {
extern Word32 BURGER_API CalcAdler32(const void *pInput,WordPtr uInputLength,Word32 uAdler32=1);
}
namespace Burger {
extern Word32 BURGER_API CalcCRC32B(const void *pInput,WordPtr uInputLength,Word32 uCRC=0);
}
namespace Burger {
extern WordPtr BURGER_API SDBMHash(const void *pInput,WordPtr uInputCount,Word32 uHashSeed = 0U);
extern WordPtr BURGER_API SDBMHashCase(const void *pInput,WordPtr uInputCount,Word32 uHashSeed = 0U);
}
namespace Burger {
extern WordPtr BURGER_API DJB2HashAdd(const void *pInput,WordPtr uInputCount,Word32 uHashSeed = 5381U);
extern WordPtr BURGER_API DJB2HashAddCase(const void *pInput,WordPtr uInputCount,Word32 uHashSeed = 5381U);
extern WordPtr BURGER_API DJB2HashXor(const void *pInput,WordPtr uInputCount,Word32 uHashSeed = 5381U);
extern WordPtr BURGER_API DJB2HashXorCase(const void *pInput,WordPtr uInputCount,Word32 uHashSeed = 5381U);
}
namespace Burger {
struct MD2_t {
	Word8 m_Hash[16];	///< 128 bit hash value in RFC 1319 MD2 format
};
struct MD2Hasher_t {
	MD2_t m_Hash;			///< Calculated hash
	Word8 m_Checksum[16];	///< Running checksum
	Word8 m_CacheBuffer[16];	///< Cached input data for multi-pass hashing
	WordPtr m_uCount;		///< Number of bytes in the cache (0-15)
	void Init(void);
	void Process(const Word8 *pBlock);
	void Process(const void *pInput,WordPtr uLength);
	void Finalize(void);
};
extern void BURGER_API Hash(MD2_t *pOutput,const void *pInput,WordPtr uLength);
}
namespace Burger {
struct MD4_t {
	Word8 m_Hash[16];	///< 128 bit hash value in RFC 1320 MD4 format
};
struct MD4Hasher_t {
	MD4_t m_Hash;				///< Current 128 bit value
	Word64 m_uByteCount;		///< Number of bytes processed (64 bit value)
	Word8 m_CacheBuffer[64];	///< input buffer for processing
	void Init(void);
	void Process(const Word8 *pBlock);
	void Process(const void *pInput,WordPtr uLength);
	void Finalize(void);
};
extern void BURGER_API Hash(MD4_t *pOutput,const void *pInput,WordPtr uLength);
}
namespace Burger {
struct MD5_t {
	Word8 m_Hash[16];	///< 128 bit hash value in RFC 1321 MD5 format
};
struct MD5Hasher_t {
	MD5_t m_Hash;				///< Current 128 bit value
	Word64 m_uByteCount;		///< Number of bytes processed (64 bit value)
	Word8 m_CacheBuffer[64];	///< input buffer for processing
	void Init(void);
	void Process(const Word8 *pBlock);
	void Process(const void *pInput,WordPtr uLength);
	void Finalize(void);
};
extern void BURGER_API Hash(MD5_t *pOutput,const void *pInput,WordPtr uLength);
}
namespace Burger {
extern float BURGER_API Unpack16ToFloat(Int16 iInput);
extern Int16 BURGER_API PackFloatTo16(float fInput);
extern float BURGER_API Unpack16ToFloat(Int16 iInput,Word32 uBaseExponent);
extern Int16 BURGER_API PackFloatTo16(float fInput,Word32 uBaseExponent);
}
namespace Burger {
struct SHA1_t {
	Word8 m_Hash[20];	///< 160 bit hash value in RFC 3174 SHA-1 format
};
struct SHA1Hasher_t {
	SHA1_t m_Hash;				///< Current 160 bit value
	Word64 m_uByteCount;		///< Number of bytes processed (64 bit value)
	Word8 m_CacheBuffer[64];	///< input buffer for processing
	void Init(void);
	void Process(const Word8 *pBlock);
	void Process(const void *pInput,WordPtr uLength);
	void Finalize(void);
};
extern void BURGER_API Hash(SHA1_t *pOutput,const void *pInput,WordPtr uLength);
}
namespace Burger {
class OutputMemoryStream;
class String;
struct Globals {
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
	enum eWindowsDLLIndex {
		DDRAW_DLL,		///< Index for ddraw.dll
		DINPUT_DLL,		///< Index for dinput.dll
		DINPUT8_DLL,	///< Index for dinput8.dll
		D3D9_DLL,		///< Index for d3d9.dll
		DSOUND_DLL,		///< Index for dsound.dll
		RPCRT4_DLL,		///< Index for rpcrt4.dll
		WINMM_DLL,		///< Index for winmm.dll
		SHLWAPI_DLL,	///< Index for shlwapi.dll
		VERSION_DLL,	///< Index for version.dll
		HID_DLL,		///< Index for hid.dll
		SETUPAPI_DLL,	///< Index for setupapi.dll
		DLL_COUNT		///< Total number of DLLs to be managed
	};
	enum eWindowsCallIndex {
		CALL_DirectInput8Create,
		CALL_DirectInputCreateW,
		CALL_DirectDrawCreate,
		CALL_DirectDrawCreateEx,
		CALL_DirectDrawCreateClipper,
		CALL_DirectDrawEnumerateA,
		CALL_DirectDrawEnumerateW,
		CALL_DirectDrawEnumerateExA,
		CALL_DirectDrawEnumerateExW,
		CALL_Direct3DCreate9,
		CALL_DirectSoundCreate,
		CALL_DirectSoundCreate8,
		CALL_UuidCreateSequential,
		CALL_timeGetTime,
		CALL_PathSearchAndQualifyA,
		CALL_PathSearchAndQualifyW,
		CALL_VerQueryValueA,
		CALL_VerQueryValueW,
		CALL_GetFileVersionInfoA,
		CALL_GetFileVersionInfoW,
		CALL_GetFileVersionInfoSizeA,
		CALL_GetFileVersionInfoSizeW,
		CALL_HidD_GetHidGuid,
		CALL_SetupDiGetClassDevsA,
		CALL_SetupDiGetClassDevsW,
		CALL_SetupDiGetDeviceInterfaceDetailA,
		CALL_SetupDiGetDeviceInterfaceDetailW,
		CALL_SetupDiEnumDeviceInterfaces,
		CALL_SetupDiDestroyDeviceInfoList,
		CALL_COUNT
	};
private:
	HINSTANCE__ *m_hInstance;				///< Current instance of the application (Windows only)
	HWND__ *m_hWindow;						///< Main window for the application (Windows only)
	HINSTANCE__ *m_hInstances[DLL_COUNT];	///< Instances of dynamically loaded system DLLs (Windows only)
	void *m_pWindowsCalls[CALL_COUNT];		///< Pointers to resolved windows function calls (Windows only)
	IDirectInput8W* m_pDirectInput8W;		///< DirectInput8W instance (Windows only)
	IDirectInputW* m_pDirectInputW;	///< DirectInputW instance (Windows only)
	Word32 m_uQuickTimeVersion;		///< QuickTime's version in 0x0102 (1.2) format. (Windows only)
	Word32 m_uDirectXVersion;		///< DirectX version 0x0900 (9.0) format (Windows only)
	Word8 m_bQuickTimeVersionValid;	///< \ref TRUE if Quicktime's version is valid. (Windows only)
	Word8 m_bDirectXVersionValid;	///< \ref TRUE if DirectX's version is valid (Windows only)
	Word8 m_bWindow95;				///< Non-zero if tested, low bit has \ref TRUE or \ref FALSE for the state
	Word8 m_bInstancesTested[DLL_COUNT];	///< Flags to determine if a DLL was tested for loading (Windows only)
#endif
private:
	int m_iErrorCode;		///< Global default error code used by \ref Globals::Shutdown().
	Word m_uTraceFlags;		///< Debug information level
	char m_ErrorMsg[512];	///< Global Buffer containing the last fatal error or warning
	Word m_bBombFlag;		///< \ref TRUE if non-fatal errors are treated as fatal
	Word m_bExitFlag;		///< Global \ref TRUE if the app is in the process of shutting down.
	static Globals g_Globals;	///< Singleton instance of the global variables
public:
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
	~Globals();
#endif
	enum {
		TRACE_MEMORYLEAKS=1,	///< Test and display memory leaks
		TRACE_REZLOAD=2,		///< Print the name of a resource file being loaded
		TRACE_FILELOAD=4,		///< Print the name of a file being loaded
		TRACE_WARNINGS=8,		///< Print possible errors
		TRACE_NETWORK=0x10,		///< Print the network commands
		TRACE_MESSAGES=0x20,	///< Print operating system messages
		TRACE_THEWORKS=0x3F		///< GIMME everything!
	};
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
	static BURGER_INLINE HINSTANCE__ *GetInstance(void) { return g_Globals.m_hInstance; }
	static BURGER_INLINE void SetInstance(HINSTANCE__ *pInput) { g_Globals.m_hInstance = pInput; }
	static BURGER_INLINE HWND__ *GetWindow(void) { return g_Globals.m_hWindow; }
	static BURGER_INLINE void SetWindow(HWND__ *pInput) { g_Globals.m_hWindow = pInput; }
	static Word BURGER_API IsDirectInputPresent(void);
	static Word BURGER_API IsDirectInput8Present(void);
	static Word BURGER_API IsDirectDrawPresent(void);
	static Word BURGER_API IsD3D9Present(void);
	static Word BURGER_API IsDirectSoundPresent(void);
	static Word BURGER_API IsWin95orWin98(void);
	static Word BURGER_API DirectInputCreateW(IDirectInputW **pOutput);
	static Word BURGER_API DirectInput8Create(IDirectInput8W **pOutput);
	static Word BURGER_API DirectDrawCreateEx(const GUID *pGuid,IDirectDraw7 **pOutput);
	static Word BURGER_API DirectDrawEnumerateExA(void *lpCallback,void *lpContext,Word32 dwFlags);
	static Word BURGER_API DirectDrawEnumerateExW(void *lpCallback,void *lpContext,Word32 dwFlags);
	static IDirect3D9 * BURGER_API Direct3DCreate9(Word uSDKVersion);
	static Word BURGER_API DirectSoundCreate(const GUID *pGuidDevice,IDirectSound **pOutput);
	static Word BURGER_API DirectSoundCreate8(const GUID *pGuidDevice,IDirectSound8 **pOutput);
	static Word BURGER_API timeGetTime(void);
	static Word BURGER_API PathSearchAndQualifyA(const char *pszPath,char *pszBuf,WordPtr cchBuf);
	static Word BURGER_API PathSearchAndQualifyW(const Word16 *pszPath,Word16 *pszBuf,WordPtr cchBuf);
	static Word BURGER_API UuidCreateSequential(GUID *pOutput);
	static Word BURGER_API VerQueryValueA(const void *pBlock,const char *lpSubBlock,void **lplpBuffer,Word *puLen);
	static Word BURGER_API VerQueryValueW(const void *pBlock,const Word16 *lpSubBlock,void **lplpBuffer,Word *puLen);
	static Word BURGER_API GetFileVersionInfoA(const char *lptstrFilename,Word32 dwHandle,Word32 dwLen,void *lpData);
	static Word BURGER_API GetFileVersionInfoW(const Word16 *lptstrFilename,Word32 dwHandle,Word32 dwLen,void *lpData);
	static Word32 BURGER_API GetFileVersionInfoSizeA(const char *lptstrFilename,unsigned long *lpdwHandle);
	static Word32 BURGER_API GetFileVersionInfoSizeW(const Word16 *lptstrFilename,unsigned long *lpdwHandle);
	static void BURGER_API HidD_GetHidGuid(GUID *HidGuid);
	static void * BURGER_API SetupDiGetClassDevsA(const GUID *ClassGuid,const char *Enumerator,HWND__ *hwndParent,Word32 Flags);
	static void * BURGER_API SetupDiGetClassDevsW(const GUID *ClassGuid,const Word16 *Enumerator,HWND__ *hwndParent,Word32 Flags);
	static Word BURGER_API SetupDiGetDeviceInterfaceDetailA(void *DeviceInfoSet,_SP_DEVICE_INTERFACE_DATA *DeviceInterfaceData,_SP_DEVICE_INTERFACE_DETAIL_DATA_A *DeviceInterfaceDetailData,Word32 DeviceInterfaceDetailDataSize,Word32 *RequiredSize,_SP_DEVINFO_DATA *DeviceInfoData);
	static Word BURGER_API SetupDiGetDeviceInterfaceDetailW(void *DeviceInfoSet,_SP_DEVICE_INTERFACE_DATA *DeviceInterfaceData,_SP_DEVICE_INTERFACE_DETAIL_DATA_W *DeviceInterfaceDetailData,Word32 DeviceInterfaceDetailDataSize,Word32 *RequiredSize,_SP_DEVINFO_DATA *DeviceInfoData);
	static Word BURGER_API SetupDiEnumDeviceInterfaces(void *DeviceInfoSet,_SP_DEVINFO_DATA *DeviceInfoData,const GUID *InterfaceClassGuid,Word32 MemberIndex,_SP_DEVICE_INTERFACE_DATA *DeviceInterfaceData);
	static Word BURGER_API SetupDiDestroyDeviceInfoList(void *DeviceInfoSet);
	static Word BURGER_API GetQuickTimeVersion(void);
	static Word BURGER_API GetDirectXVersion(void);
	static Word BURGER_API GetVideoGUID(GUID *pOutput,Word uDevNum);
	static HINSTANCE__ * BURGER_API LoadLibraryA(const char *pInput);
	static HINSTANCE__ * BURGER_API LoadLibraryW(const Word16 *pInput);
	static HINSTANCE__ * BURGER_API LoadLibraryIndex(eWindowsDLLIndex eIndex);
	static void * BURGER_API LoadFunctionIndex(eWindowsCallIndex eIndex);
	static Word BURGER_API AddGroupToProgramMenu(const char *pGroupName);
	static int BURGER_API CreateUserRegistryKey(const char *pKey,const char *pSubKey,const char *pData);
	static void BURGER_API AssociateFileExtensionToExe(const char *pFileExtension,const char *pDescription,const char *pProgramID);
#endif
#if defined(BURGER_MACOSX) || defined(DOXYGEN)
	static void BURGER_API AddToMenubar(NSMenu *pNSMenu);
	static NSString *BURGER_API GetApplicationName(void);
	static void BURGER_API CreateApplicationMenu(void);
	static void BURGER_API CreateWindowMenu(void);
	static void BURGER_API CreateViewMenu(void);
	static void BURGER_API CreateHelpMenu(void);
	static void BURGER_API CreateDefaultMenus(void);
	static void BURGER_API StringCopy(String *pOutput,const __CFString *pInput);
	static void BURGER_API GetHIDDeviceName(String *pOutput,__IOHIDDevice *pDevice);
	static __CFDictionary * BURGER_API CreateHIDDictionary(Word uPage,Word uUsage);
	static void GetDisplayName(String *pOutput,Word uDisplayID);
	static int NumberFromKey(const __CFDictionary *pDictionary,const char *pKey);
#endif
	static BURGER_INLINE int GetErrorCode(void) { return g_Globals.m_iErrorCode; }
	static BURGER_INLINE void SetErrorCode(int iNewError) { g_Globals.m_iErrorCode = iNewError; }
	static BURGER_INLINE char *GetErrorMsg(void) { return g_Globals.m_ErrorMsg; }
	static void BURGER_ANSIAPI SetErrorMsg(const char *pMessage,...);
	static BURGER_INLINE Word GetTraceFlag(void) { return g_Globals.m_uTraceFlags; }
	static BURGER_INLINE void SetTraceFlag(Word uNewFlag) { g_Globals.m_uTraceFlags = uNewFlag; }
	static BURGER_INLINE Word AreWarningsEnabled(void) { return g_Globals.m_uTraceFlags&TRACE_WARNINGS; }
	static BURGER_INLINE Word GetErrorBombFlag(void) { return g_Globals.m_bBombFlag; }
	static BURGER_INLINE Word SetErrorBombFlag(Word uNewFlag) { Word uOld = g_Globals.m_bBombFlag; g_Globals.m_bBombFlag = uNewFlag; return uOld; }
	static BURGER_INLINE Word GetExitFlag(void) { return g_Globals.m_bExitFlag; }
	static BURGER_INLINE void SetExitFlag(Word uNewFlag) { g_Globals.m_bExitFlag = uNewFlag; }
	static void BURGER_API Shutdown(void);
	static void BURGER_API Shutdown(int iError);
	static Word BURGER_API Version(void);
	static Word BURGER_API LaunchURL(const char *pURL);
	static int BURGER_API ExecuteTool(const char *pFilename,const char *pParameters,OutputMemoryStream *pOutput=NULL);
	static const char * BURGER_API GetEnvironmentString(const char *pKey);
	static Word BURGER_API SetEnvironmentString(const char *pKey,const char *pInput);
};
}
namespace Burger {
class String {
public:
	static const Word BUFFERSIZE = 64-static_cast<int>(sizeof(char *)+sizeof(WordPtr));	///< Ensures the structure is 64 bytes in size on all platforms
private:
	char *m_pData;			///< Pointer to the string
	WordPtr m_uLength;		///< Length of the string
	char m_Raw[BUFFERSIZE];	///< Temp preallocated buffer for most strings
public:
	String(void) { m_pData = m_Raw;m_uLength=0;m_Raw[0]=0;}
	String(const String &rInput);
	String(const String &rInput,WordPtr uStart,WordPtr uEnd = BURGER_MAXWORDPTR);
	String(const char *pInput);
	String(const char *pInput,WordPtr uPadding);
	String(const Word16 *pInput);
	String(const Word32 *pInput);
	String(const char *pInput,WordPtr uStart,WordPtr uEnd);
	String(char cInput);
	String(char cInput,WordPtr uFillSize);
	String(const char *pInput1,const char *pInput2);
	String(const char *pInput1,const char *pInput2,const char *pInput3);
	String(const char *pInput1,const char *pInput2,const char *pInput3,const char *pInput4);
	~String() { if (m_pData != m_Raw) Burger::Free(m_pData); }
	BURGER_INLINE operator char *() { return m_pData; }
	BURGER_INLINE operator const char *() const { return m_pData; }
	BURGER_INLINE const char *c_str() const { return m_pData; }
	BURGER_INLINE char *c_str() { return m_pData; }
	BURGER_INLINE operator char () const { return m_pData[0]; }
	BURGER_INLINE WordPtr length(void) const { return m_uLength; }
	BURGER_INLINE WordPtr GetLength(void) const { return m_uLength; }
	BURGER_INLINE char *GetPtr() { return m_pData; }
	BURGER_INLINE const char *GetPtr() const { return m_pData; }
	void BURGER_API Set(const char *pInput);
	void BURGER_API Set(const char *pInput,WordPtr uLength);
	void BURGER_API SetBufferSize(WordPtr uSize);
	String & operator = (const String &rInput);
	String & operator = (const char *pInput);
	String & operator = (char cInput);
	String & operator += (const String &rInput);
	String & operator += (const char *pInput);
	String & operator += (char cInput);
	BURGER_INLINE String operator () (WordPtr uStart,WordPtr uEnd) const {return String(*this,uStart,uEnd);}
	BURGER_INLINE char & operator () (WordPtr uInput) { if (uInput>=m_uLength) { m_Raw[BUFFERSIZE-1] = 0; return m_Raw[BUFFERSIZE-1]; } return m_pData[uInput];}
	BURGER_INLINE char const & operator ()(WordPtr uInput) const { if (uInput>=m_uLength) { return g_EmptyString[0]; } return m_pData[uInput];}
	BURGER_INLINE char & operator [] (WordPtr uInput) { if (uInput>=m_uLength) { m_Raw[BUFFERSIZE-1] = 0; return m_Raw[BUFFERSIZE-1]; } return m_pData[uInput];}
	BURGER_INLINE char const & operator [](WordPtr uInput) const { if (uInput>=m_uLength) { return g_EmptyString[0]; } return m_pData[uInput];}
	char BURGER_API Get(WordPtr uWhere) const;
	void BURGER_API Put(WordPtr uWhere,char cInput);
	char * BURGER_API StringString(const char *pInput) const;
	BURGER_INLINE String & ToLowercase(void) { Burger::StringLowercase(this->m_pData); return *this; }
	BURGER_INLINE String & ToUppercase(void) { Burger::StringUppercase(this->m_pData); return *this; }
	BURGER_INLINE String Lowercase(void) const { return String(*this).ToLowercase(); }
	BURGER_INLINE String Uppercase(void) const { return String(*this).ToUppercase(); }
	BURGER_INLINE Word operator ! () const { return (m_uLength==0); }
	BURGER_INLINE Word IsValid(void) const { return (m_uLength!=0); }
	void BURGER_API Clear(void);
	WordPtr BURGER_API Copy(char *pOutput,WordPtr uOutputSize = static_cast<WordPtr>(-1)) const;
	WordPtr BURGER_API PCopy(Word8 *pOutput,WordPtr uOutputSize = 256) const;
	WordPtr BURGER_API Remove(WordPtr uStart,WordPtr uLength=static_cast<WordPtr>(-1));
	WordPtr BURGER_API Insert(WordPtr uStart,const char *pInput,WordPtr uInputSize);
	WordPtr BURGER_API Append(const char *pInput,WordPtr uInputSize);
	String & BURGER_API Left(WordPtr uNewLength,char cPad=' ');
	String & BURGER_API Right(WordPtr uNewLength,char cPad=' ');
	BURGER_INLINE int Compare(const String &rInput) const { return StringCompare(m_pData,rInput.GetPtr()); }
	int BURGER_API Compare(const char *pInput) const;
	int BURGER_API Compare(char cInput) const;
	WordPtr BURGER_API RemoveChars(const char *pInput);
	WordPtr BURGER_API RemoveChar(char cInput);
	WordPtr BURGER_API NormalizeLineFeeds(void);
	BURGER_INLINE Word GetBoolean(Word bDefault) const { return AsciiToBoolean(m_pData,bDefault); }
	void BURGER_API SetTrueFalse(Word bInput);
	void BURGER_API SetYesNo(Word bInput);
	Word BURGER_API GetWord(Word uDefault,Word uMin=0,Word uMax=BURGER_MAXUINT) const { return AsciiToWord(m_pData,uDefault,uMin,uMax); }
	void BURGER_API SetWord(Word uInput);
	void BURGER_API SetWordHex(Word uInput);
	BURGER_INLINE Int GetInt(Int iDefault,Int iMin=(-BURGER_MAXINT)-1,Int iMax=BURGER_MAXINT) const { return AsciiToInteger(m_pData,iDefault,iMin,iMax); }
	void BURGER_API SetInt(Int iInput);
	BURGER_INLINE float GetFloat(float fDefault) const { return AsciiToFloat(m_pData,fDefault); }
	BURGER_INLINE float GetFloat(float fDefault,float fMin,float fMax) const { return AsciiToFloat(m_pData,fDefault,fMin,fMax); }
	void BURGER_API SetFloat(float fValue);
	BURGER_INLINE double GetDouble(double dDefault) const { return AsciiToDouble(m_pData,dDefault); }
	BURGER_INLINE double GetDouble(double dDefault,double dMin,double dMax) const { return AsciiToDouble(m_pData,dDefault,dMin,dMax); }
	void BURGER_API SetDouble(double fValue);
	void BURGER_API SetFast(const char *pInput);
	void BURGER_API SetFast(const char *pInput,WordPtr uLength);
	BURGER_INLINE friend Word operator == (String const &rInput1,String const &rInput2) { return static_cast<Word>(Burger::StringCompare(rInput1.c_str(),rInput2.c_str())==0); }
	BURGER_INLINE friend Word operator == (String const &rInput1,const char *pInput2) { return static_cast<Word>(rInput1.Compare(pInput2)==0); }
	BURGER_INLINE friend Word operator == (const char *pInput1,String const &rInput2) { return static_cast<Word>(rInput2.Compare(pInput1)==0); }
	BURGER_INLINE friend Word operator == (String const &rInput1,char cInput2) { return static_cast<Word>(rInput1.Compare(cInput2)==0); }
	BURGER_INLINE friend Word operator == (char cInput1,String const &rInput2) { return static_cast<Word>(rInput2.Compare(cInput1)==0); }
	BURGER_INLINE friend Word operator != (String const &rInput1,String const &rInput2) { return static_cast<Word>(Burger::StringCompare(rInput1.c_str(),rInput2.c_str())!=0); }
	BURGER_INLINE friend Word operator != (String const &rInput1,const char *pInput2) { return static_cast<Word>(rInput1.Compare(pInput2)!=0); }
	BURGER_INLINE friend Word operator != (const char *pInput1,String const &rInput2) { return static_cast<Word>(rInput2.Compare(pInput1)!=0); }
	BURGER_INLINE friend Word operator != (String const &rInput1,char cInput2) { return static_cast<Word>(rInput1.Compare(cInput2)!=0); }
	BURGER_INLINE friend Word operator != (char cInput1,String const &rInput2) { return static_cast<Word>(rInput2.Compare(cInput1)!=0); }
	BURGER_INLINE friend Word operator < (String const &rInput1,String const &rInput2) { return static_cast<Word>(Burger::StringCompare(rInput1.c_str(),rInput2.c_str())<0); }
	BURGER_INLINE friend Word operator < (String const &rInput1,const char *pInput2) { return static_cast<Word>(rInput1.Compare(pInput2)<0); }
	BURGER_INLINE friend Word operator < (const char *pInput1,String const &rInput2) { return static_cast<Word>(rInput2.Compare(pInput1)>0); }
	BURGER_INLINE friend Word operator < (String const &rInput1,char cInput2) { return static_cast<Word>(rInput1.Compare(cInput2)<0); }
	BURGER_INLINE friend Word operator < (char cInput1,String const &rInput2) { return static_cast<Word>(rInput2.Compare(cInput1)>0); }
	BURGER_INLINE friend Word operator <= (String const &rInput1,String const &rInput2) { return static_cast<Word>(Burger::StringCompare(rInput1.c_str(),rInput2.c_str())<=0); }
	BURGER_INLINE friend Word operator <= (String const &rInput1,const char *pInput2) { return static_cast<Word>(rInput1.Compare(pInput2)<=0); }
	BURGER_INLINE friend Word operator <= (const char *pInput1,String const &rInput2) { return static_cast<Word>(rInput2.Compare(pInput1)>=0); }
	BURGER_INLINE friend Word operator <= (String const &rInput1,char cInput2) { return static_cast<Word>(rInput1.Compare(cInput2)<=0); }
	BURGER_INLINE friend Word operator <= (char cInput1,String const &rInput2) { return static_cast<Word>(rInput2.Compare(cInput1)>=0); }
	BURGER_INLINE friend Word operator > (String const &rInput1,String const &rInput2) { return static_cast<Word>(Burger::StringCompare(rInput1.c_str(),rInput2.c_str())>0); }
	BURGER_INLINE friend Word operator > (String const &rInput1,const char *pInput2) { return static_cast<Word>(rInput1.Compare(pInput2)>0); }
	BURGER_INLINE friend Word operator > (const char *pInput1,String const &rInput2) { return static_cast<Word>(rInput2.Compare(pInput1)<0); }
	BURGER_INLINE friend Word operator > (String const &rInput1,char cInput2) { return static_cast<Word>(rInput1.Compare(cInput2)>0); }
	BURGER_INLINE friend Word operator > (char cInput1,String const &rInput2) { return static_cast<Word>(rInput2.Compare(cInput1)<0); }
	BURGER_INLINE friend Word operator >= (String const &rInput1,String const &rInput2) { return static_cast<Word>(Burger::StringCompare(rInput1.c_str(),rInput2.c_str())>=0); }
	BURGER_INLINE friend Word operator >= (String const &rInput1,const char *pInput2) { return static_cast<Word>(rInput1.Compare(pInput2)>=0); }
	BURGER_INLINE friend Word operator >= (const char *pInput1,String const &rInput2) { return static_cast<Word>(rInput2.Compare(pInput1)<=0); }
	BURGER_INLINE friend Word operator >= (String const &rInput1,char cInput2) { return static_cast<Word>(rInput1.Compare(cInput2)>=0); }
	BURGER_INLINE friend Word operator >= (char cInput1,String const &rInput2) { return static_cast<Word>(rInput2.Compare(cInput1)<=0); }
};
}
namespace Burger {
class String16 {
public:
	static const Word BUFFERSIZE = static_cast<Word>((128-(sizeof(Word16 *)+sizeof(WordPtr)))/sizeof(Word16));	///< Ensures the structure is 128 bytes in size on all platforms
private:
	Word16 *m_pData;		///< Pointer to the string
	WordPtr m_uLength;		///< Length of the string
	Word16 m_Raw[BUFFERSIZE];	///< Temp preallocated buffer for most strings
public:
	String16(void) { m_pData = m_Raw;m_uLength=0;m_Raw[0]=0;}
	String16(const String16 &rInput);
	String16(const String16 &rInput,WordPtr uStart,WordPtr uEnd = static_cast<WordPtr>(-1));
	String16(const char *pInput);
	String16(const char *pInput,WordPtr uPadding);
	String16(const Word16 *pInput);
	~String16() { if (m_pData != m_Raw) Burger::Free(m_pData); }
	BURGER_INLINE operator Word16 *() { return m_pData; }
	BURGER_INLINE operator const Word16 *() const { return m_pData; }
	BURGER_INLINE const Word16 *c_str() const { return m_pData; }
	BURGER_INLINE Word16 *c_str() { return m_pData; }
	BURGER_INLINE operator Word16 () const { return m_pData[0]; }
	BURGER_INLINE WordPtr length(void) const { return m_uLength; }
	BURGER_INLINE WordPtr GetLength(void) const { return m_uLength; }
	BURGER_INLINE Word16 *GetPtr() { return m_pData; }
	BURGER_INLINE const Word16 *GetPtr() const { return m_pData; }
	void BURGER_API SetBufferSize(WordPtr uSize);
	BURGER_INLINE String16 operator () (WordPtr uStart,WordPtr uEnd) const {return String16(*this,uStart,uEnd);}
	BURGER_INLINE Word16 & operator () (WordPtr uInput) { if (uInput>=m_uLength) { m_Raw[BUFFERSIZE-1] = 0; return m_Raw[BUFFERSIZE-1]; } return m_pData[uInput];}
	BURGER_INLINE Word16 const & operator ()(WordPtr uInput) const { if (uInput>=m_uLength) { return g_EmptyString16[0]; } return m_pData[uInput];}
	BURGER_INLINE Word16 & operator [] (WordPtr uInput) { if (uInput>=m_uLength) { m_Raw[BUFFERSIZE-1] = 0; return m_Raw[BUFFERSIZE-1]; } return m_pData[uInput];}
	BURGER_INLINE Word16 const & operator [](WordPtr uInput) const { if (uInput>=m_uLength) { return g_EmptyString16[0]; } return m_pData[uInput];}
	BURGER_INLINE Word operator ! () const { return (m_uLength==0); }
	BURGER_INLINE Word IsValid(void) const { return (m_uLength!=0); }
	void Clear(void);
};
}
namespace Burger {
extern WordPtr BURGER_API SDBMHashFunctor(const void *pData,WordPtr uDataSize);
extern WordPtr BURGER_API SDBMHashCaseFunctor(const void *pData,WordPtr uDataSize);
extern WordPtr BURGER_API DJB2HashAddFunctor(const void *pData,WordPtr uDataSize);
extern WordPtr BURGER_API DJB2HashAddCaseFunctor(const void *pData,WordPtr uDataSize);
extern WordPtr BURGER_API DJB2HashXorFunctor(const void *pData,WordPtr uDataSize);
extern WordPtr BURGER_API DJB2HashXorCaseFunctor(const void *pData,WordPtr uDataSize);
extern WordPtr BURGER_API DJB2StringHashXorFunctor(const void *pData,WordPtr uDataSize);
extern WordPtr BURGER_API DJB2StringHashXorCaseFunctor(const void *pData,WordPtr uDataSize);
class HashMapShared {
protected:
	static const WordPtr INVALID_HASH = BURGER_MAXWORDPTR;		///< Invalid hash value for marking an Entry as uninitialized
	static const WordPtr INVALID_INDEX = BURGER_MAXWORDPTR;		///< Error value for invalid indexes
	static const WordPtr END_OF_CHAIN = BURGER_MAXWORDPTR;		///< Constant to mark the end of a hash chain
	static const WordPtr EMPTY_RECORD = BURGER_MAXWORDPTR-1;	///< Constant to mark an unused hash record
public:
	struct Entry {
		WordPtr m_uNextInChain;	///< Next item index in the linked list chain or \ref END_OF_CHAIN to mark the end of a linked list
		WordPtr m_uHashValue;	///< Computed hash value for this object (\ref INVALID_HASH indicates this entry is not initialized)
		BURGER_INLINE Word IsEmpty(void) const { return m_uNextInChain == EMPTY_RECORD; }
		BURGER_INLINE Word IsEndOfChain(void) const { return m_uNextInChain == END_OF_CHAIN; }
		BURGER_INLINE Word IsHashInvalid(void) const { return m_uHashValue == INVALID_HASH; }
	};
protected:
	typedef WordPtr (BURGER_API *HashProc)(const void *pData,WordPtr uDataSize);	///< Function prototype for user supplied hash generator
	typedef Word (BURGER_API *TestProc)(const void *pA,const void *pB);				///< Function prototype for testing keys
	typedef void (BURGER_API *EntryConstructProc)(Entry *pEntry);					///< Function prototype for destroying entries
	typedef void (BURGER_API *EntryCopyProc)(Entry *pEntry,const void *pT,const void *pU);	///< Function prototype for destroying entries
	typedef void (BURGER_API *EntryInvalidateProc)(Entry *pEntry);					///< Function prototype for destroying entries
	void *m_pEntries;			///< Pointer to the hash table Burger::Alloc(m_uEntrySize*(m_uSizeMask+1))
	WordPtr m_uEntrySize;		///< Size in bytes of each entry in the table
	WordPtr m_uFirstSize;		///< Size of the key in bytes
	WordPtr m_uSecondOffset;	///< Offset in bytes to the start of the data chunk
	WordPtr m_uEntryCount;		///< Number of valid entries in the hash
	WordPtr m_uSizeMask;		///< (Power of 2)-1 size mask used for masking indexes for instant table rounding
	HashProc m_pHashFunction;	///< Pointer to the hash function
	TestProc m_pTestFunction;	///< Pointer to the equality test function
	EntryConstructProc m_pEntryConstructFunction;		///< Pointer to function to construct Entry data
	EntryCopyProc m_pEntryCopyFunction;					///< Pointer to function to copy construct Entry data
	EntryInvalidateProc m_pEntryInvalidationFunction;	///< Pointer to function to destroy data in an Entry
	HashMapShared(WordPtr uEntrySize,WordPtr uFirstSize,WordPtr uSecondOffset,
		TestProc pTestFunction,EntryConstructProc pEntryConstructFunction,
		EntryCopyProc pEntryCopyFunction,EntryInvalidateProc pEntryInvalidationFunction,
		HashProc pHashFunction=SDBMHashFunctor) :
		m_pEntries(NULL),
		m_uEntrySize(uEntrySize),
		m_uFirstSize(uFirstSize),
		m_uSecondOffset(uSecondOffset),
		m_uEntryCount(0),
		m_uSizeMask(0),
		m_pHashFunction(pHashFunction),
		m_pTestFunction(pTestFunction),
		m_pEntryConstructFunction(pEntryConstructFunction),
		m_pEntryCopyFunction(pEntryCopyFunction),
		m_pEntryInvalidationFunction(pEntryInvalidationFunction)
	{
	}
	WordPtr BURGER_API FindIndex(const void *pKey) const;
	void BURGER_API CreateBuffer(WordPtr uCount,WordPtr uEntrySize);
	void BURGER_API CreateHashBuffer(WordPtr uNewSize);
	void BURGER_API Erase(WordPtr uIndex);
	void BURGER_API Erase(const void *pKey);
	WordPtr BURGER_API FindFirst(void) const;
	WordPtr BURGER_API ComputeHash(const void *pKey) const;
	void BURGER_API Copy(const HashMapShared *pInput);
	void BURGER_API Add(const void *pT,const void *pU);
	const void* BURGER_API GetData(const void *pT) const;
	BURGER_INLINE Entry *GetEntry(WordPtr uIndex)
	{
		BURGER_ASSERT(m_pEntries && (uIndex <= m_uSizeMask));
		return reinterpret_cast<Entry *>(static_cast<Word8 *>(m_pEntries) + (uIndex*m_uEntrySize));
	}
	BURGER_INLINE const Entry *GetEntry(WordPtr uIndex) const
	{
		BURGER_ASSERT(m_pEntries && (uIndex <= m_uSizeMask));
		return reinterpret_cast<const Entry *>(static_cast<const Word8 *>(m_pEntries) + (uIndex*m_uEntrySize));
	}
public:
	class const_iterator {
	protected:
		const HashMapShared* m_pParent;	///< Pointer to the parent class instance
		WordPtr m_uIndex;				///< Last accessed index
		const_iterator(const HashMapShared *pParent,WordPtr uIndex) :
			m_pParent(pParent),m_uIndex(uIndex)
		{
		}
	public:
		BURGER_INLINE Word IsEnd(void) const { return (m_uIndex == INVALID_INDEX); }
		BURGER_INLINE const Entry *GetPtr(void) const {
			const Entry *pEntry = m_pParent->GetEntry(m_uIndex);
			BURGER_ASSERT(!IsEnd() && !pEntry->IsEmpty() && !pEntry->IsHashInvalid());
			return pEntry;
		}
		BURGER_INLINE const Entry &operator*() const { return GetPtr()[0]; }
		BURGER_INLINE const Entry *operator->() const { return GetPtr(); }
		void BURGER_API operator++();
		BURGER_INLINE Word operator==(const const_iterator& it) const {
			return (m_pParent == it.m_pParent) && (m_uIndex == it.m_uIndex);
		}
		BURGER_INLINE Word operator!=(const const_iterator& it) const {
			return (m_pParent != it.m_pParent) || (m_uIndex != it.m_uIndex);
		}
	};
	void BURGER_API Clear(void);
	void BURGER_API Resize(WordPtr uNewSize);
	void BURGER_API SetCapacity(WordPtr uNewSize);
	BURGER_INLINE WordPtr GetEntryCount(void) const { return m_uEntryCount; }
	BURGER_INLINE WordPtr GetSizeMask(void) const { return m_uSizeMask; }
	BURGER_INLINE Word IsEmpty(void) const { return (m_uEntryCount == 0); }
	BURGER_INLINE WordPtr GetEntrySize(void) const { return m_uEntrySize; }
};
template<class T, class U >
class HashMap : public HashMapShared {
	struct Entry : public HashMapShared::Entry {
		T first;				///< Key value
		U second;				///< Data associated with the key
	};
	static void BURGER_API Construct(HashMapShared::Entry *pEntry)
	{
		new (&static_cast<Entry *>(pEntry)->first) T;
		new (&static_cast<Entry *>(pEntry)->second) U;
	}
	static void BURGER_API Copy(HashMapShared::Entry *pEntry,const void *pT,const void *pU)
	{
		new (&static_cast<Entry *>(pEntry)->first) T(static_cast<const T*>(pT)[0]);
		new (&static_cast<Entry *>(pEntry)->second) U(static_cast<const U*>(pU)[0]);
	}
	static void BURGER_API Invalidate(HashMapShared::Entry *pEntry)
	{
		static_cast<Entry *>(pEntry)->first.~T();
		static_cast<Entry *>(pEntry)->second.~U();
	}
	static Word BURGER_API EqualsTest(const void *pA,const void *pB) { return static_cast<const T *>(pA)[0] == static_cast<const T *>(pB)[0]; }
public:
	HashMap(HashProc pHashFunction = SDBMHashFunctor) :
		HashMapShared(sizeof(Entry),sizeof(T),BURGER_OFFSETOF(Entry,second),
		EqualsTest,Construct,Copy,Invalidate,pHashFunction) { }
	HashMap(HashProc pHashFunction,TestProc pTestProc) :
		HashMapShared(sizeof(Entry),sizeof(T),BURGER_OFFSETOF(Entry,second),
			pTestProc,Construct,Copy,Invalidate,pHashFunction) { }
	HashMap(HashProc pHashFunction,WordPtr uDefault) :
		HashMapShared(sizeof(Entry),sizeof(T),BURGER_OFFSETOF(Entry,second),
		EqualsTest,Construct,Copy,Invalidate,pHashFunction) { SetCapacity(uDefault); }
	HashMap(const HashMap<T,U>& rHashMap) :
		HashMapShared(rHashMap.m_uEntrySize,rHashMap.m_uFirstSize,rHashMap.m_uSecondOffset,
		rHashMap.m_pTestFunction,rHashMap.m_pEntryConstructFunction,rHashMap.m_pEntryCopyFunction,
		rHashMap.m_pEntryInvalidationFunction,rHashMap.m_pHashFunction) {
		HashMapShared::Copy(&rHashMap);
	}
	~HashMap() { Clear(); }
	HashMap<T,U>& operator=(const HashMap<T,U>& rHashMap)
	{
		if (&rHashMap!=this) {
			Copy(&rHashMap);
		}
		return *this;
	}
	U &operator[](const T& rKey)
	{
		WordPtr uIndex = HashMapShared::FindIndex(&rKey);
		if (uIndex==INVALID_INDEX) {
			add(rKey,U());
			uIndex = HashMapShared::FindIndex(&rKey);
			if (uIndex==INVALID_INDEX) {
				BURGER_ASSERT(0);
			}
		}
		return static_cast<Entry *>(GetEntry(uIndex))->second;
	}
	void Set(const T &rKey,const U &rValue)
	{
		WordPtr	uIndex = HashMapShared::FindIndex(&rKey);
		if (uIndex==INVALID_INDEX) {
			Add(&rKey,&rValue);
		} else {
			static_cast<Entry *>(GetEntry(uIndex))->second = rValue;
		}
	}
	BURGER_INLINE void add(const T &rKey,const U &rValue) { Add(&rKey,&rValue); }
	BURGER_INLINE U *GetData(const T& rKey) { return const_cast<U*>(static_cast<const U*>(HashMapShared::GetData(&rKey))); }
	BURGER_INLINE const U *GetData(const T& rKey) const { return static_cast<const U*>(HashMapShared::GetData(&rKey)); }
	Word GetData(const T& rKey,U *pOutput) const
	{
		const U *pResult = static_cast<const U*>(HashMapShared::GetData(&rKey));
		Word uResult = FALSE;
		if (pResult) {
			pOutput[0] = pResult[0];
			uResult = TRUE;
		}
		return uResult;
	}
	class iterator;
	class const_iterator : public HashMapShared::const_iterator {
		const_iterator(const HashMapShared*pParent,WordPtr uIndex) : HashMapShared::const_iterator(pParent,uIndex) {}
		friend class HashMap<T,U>;
		friend class iterator;
	public:
		BURGER_INLINE const Entry &operator*() const { return static_cast<const Entry *>(GetPtr())[0]; }
		BURGER_INLINE const Entry *operator->() const { return static_cast<const Entry *>(GetPtr()); }
	};
	class iterator : public const_iterator {
		friend class HashMap<T,U>;
		iterator(HashMapShared*pParent,WordPtr uIndex) : const_iterator(pParent,uIndex) {}
	public:
		BURGER_INLINE Entry &operator*() const { return const_cast<Entry *>(static_cast<const Entry *>(HashMapShared::const_iterator::GetPtr()))[0]; }
		BURGER_INLINE Entry *operator->() const { return const_cast<Entry *>(static_cast<const Entry *>(HashMapShared::const_iterator::GetPtr())); }
	};
	BURGER_INLINE iterator begin(void) { return iterator(this,FindFirst()); }
	BURGER_INLINE const_iterator begin(void) const { return const_iterator(this,FindFirst()); }
	BURGER_INLINE iterator end(void) { return iterator(this,INVALID_INDEX); }
	BURGER_INLINE const_iterator end(void) const { return const_iterator(this,INVALID_INDEX); }
	BURGER_INLINE iterator find(const T& rKey) { return iterator(this,HashMapShared::FindIndex(&rKey)); }
	BURGER_INLINE const_iterator find(const T& rKey) const { return const_iterator(this,HashMapShared::FindIndex(&rKey)); }
	void erase(const iterator& it)
	{
		if (!it.IsEnd() && it.m_pParent == this) {
			Erase(it.m_uIndex);
		}
	}
	BURGER_INLINE void erase(const T& rKey) { HashMapShared::Erase(&rKey); }
};
template<class U>
class HashMapString : public HashMap<String,U > {
public: HashMapString() : HashMap<String,U >(DJB2StringHashXorFunctor) {}
};
extern Word BURGER_API HashMapStringCaseTest(const void *pA,const void *pB);
template<class U>
class HashMapStringCase : public HashMap<String,U > {
public: HashMapStringCase() : HashMap<String,U >(DJB2StringHashXorCaseFunctor,HashMapStringCaseTest) {}
};
}
#if (defined(BURGER_X86) || defined(BURGER_AMD64)) || defined(DOXYGEN)
extern "C" const float g_fBurgerIntMathNearesttable[2];
extern "C" const float g_fBurgerMath65536;
#endif
#define FLOATTOFIXED(x) static_cast<Fixed32>((x)*65536.0f)
#define FIXEDTOFLOAT(x) (static_cast<float>(x)*(1.0f/65536.0f))
#define INTTOFIXED(x) static_cast<Fixed32>((x)<<16)
#define FIXEDTOINT(x) static_cast<int>((x+((x>>31)&0xFFFF))>>16)
namespace Burger {
	const Word16 MaxWord16 = 0xFFFFU;			///< Maximum value for \ref Word16 (Minimum is 0)
	const Word32 MaxWord32 = 0xFFFFFFFFU;		///< Maximum value for \ref Word32 (Minimum is 0)
	const Word64 MaxWord64 = 0xFFFFFFFFFFFFFFFFULL;	///< Maximum value for \ref Word64 (Minimum is 0)
	const Int16 MinInt16 = (-0x7FFF)-1;			///< Minimum value for \ref Int16
	const Int16 MaxInt16 = 0x7FFF;				///< Maximum value for \ref Int16
	const Int32 MinInt32 = (-0x7FFFFFFF)-1;	///< Minimum value for \ref Int32
	const Int32 MaxInt32 = 0x7FFFFFFF;			///< Maximum value for \ref Int32
	const Int64 MinInt64 = (-0x7FFFFFFFFFFFFFFFLL)-1;	///< Minimum value for \ref Int64
	const Int64 MaxInt64 = 0x7FFFFFFFFFFFFFFFLL;		///< Maximum value for \ref Int64
	const Frac32 MinFrac32 = (-0x7FFFFFFF)-1;	///< Minimum value for \ref Frac32
	const Frac32 MaxFrac32 = 0x7FFFFFFF;		///< Maximum value for \ref Frac32
	const Fixed32 MinFixed32 = (-0x7FFFFFFF)-1;///< Minimum value for \ref Fixed32
	const Fixed32 MaxFixed32 = 0x7FFFFFFF;		///< Maximum value for \ref Fixed32
	const Fixed32 PiFixed32 = 0x003243F;		///< Pi in \ref Fixed32 format (3.141... * 65536 = 205887.416)
	BURGER_INLINE Word GetLoWord(Word32 uInput) { return (uInput&0xFFFFU); }
	BURGER_INLINE Word GetHiWord(Word32 uInput) { return (uInput>>16); }
	BURGER_INLINE Fixed32 IntToFixed(Int32 iInput) { return static_cast<Fixed32>(iInput<<16); }
	extern Fixed32 BURGER_API IntToFixedSaturate(Int32 iInput);
	BURGER_INLINE Int32 FixedToIntFloor(Fixed32 fInput) { return static_cast<Int32>(fInput>>16); }
	BURGER_INLINE Int32 FixedToInt(Fixed32 fInput) { return static_cast<Int32>((fInput+((fInput>>31)&0xFFFF))>>16); }
	BURGER_INLINE Int32 FixedToIntCeil(Fixed32 fInput) { return static_cast<Int32>((fInput+0xFFFF)>>16); }
	BURGER_INLINE Int32 FixedToIntNearest(Fixed32 fInput) { return static_cast<Int32>((fInput+0x8000)>>16); }
#if defined(BURGER_WATCOM)
	BURGER_INLINE Int32 FloatToIntFloor(float fInput) { return BurgerIntMathFromFloatFloor(fInput); }
	BURGER_INLINE Int32 FloatToInt(float fInput) { return BurgerIntMathFromFloat(fInput); }
	BURGER_INLINE Int32 FloatToIntCeil(float fInput) { return BurgerIntMathFromFloatCeil(fInput); }
	BURGER_INLINE Int32 FloatToIntNearest(float fInput) { return BurgerIntMathFromFloatNearest(fInput); }
	BURGER_INLINE void FloatToIntFloor(Int32 *pOutput,float fInput) { BurgerIntMathFromFloatFloor2(pOutput,fInput); }
	BURGER_INLINE void FloatToInt(Int32 *pOutput,float fInput) { BurgerIntMathFromFloat2(pOutput,fInput); }
	BURGER_INLINE void FloatToIntCeil(Int32 *pOutput,float fInput) { BurgerIntMathFromFloatCeil2(pOutput,fInput); }
	BURGER_INLINE void FloatToIntNearest(Int32 *pOutput,float fInput) { BurgerIntMathFromFloatNearest2(pOutput,fInput); }
#elif defined(BURGER_XBOX360) && !defined(DOXYGEN)
	BURGER_INLINE Int32 FloatToIntFloor(float fInput) { Int32 iResult; __stfiwx(__fctiw(fInput-0.5f),0,&iResult); return iResult; }
	BURGER_INLINE Int32 FloatToInt(float fInput) { Int32 iResult; __stfiwx(__fctiwz(fInput),0,&iResult); return iResult; }
	BURGER_INLINE Int32 FloatToIntCeil(float fInput) { Int32 iResult; __stfiwx(__fctiw(fInput+(0.5f-(1.0f/(65536.0f*256.0f)))),0,&iResult); return iResult; }
	BURGER_INLINE Int32 FloatToIntNearest(float fInput) { Int32 iResult; __stfiwx(__fctiw(fInput),0,&iResult); return iResult; }
#if _MSC_FULL_VER!=14007151	// This compiler has a bug
	BURGER_INLINE void FloatToIntFloor(Int32 *pOutput,float fInput) { __stfiwx(__fctiw(fInput-0.5f),0,pOutput); }
	BURGER_INLINE void FloatToInt(Int32 *pOutput,float fInput) { __stfiwx(__fctiwz(fInput),0,pOutput); }
	BURGER_INLINE void FloatToIntCeil(Int32 *pOutput,float fInput) { __stfiwx(__fctiw(fInput+(0.5f-(1.0f/(65536.0f*256.0f)))),0,pOutput); }
	BURGER_INLINE void FloatToIntNearest(Int32 *pOutput,float fInput) { __stfiwx(__fctiw(fInput),0,pOutput); }
#else	// Workaround until the bug is fixed
	BURGER_INLINE void FloatToIntFloor(Int32 *pOutput,float fInput) { pOutput[0] = FloatToIntFloor(fInput); }
	BURGER_INLINE void FloatToInt(Int32 *pOutput,float fInput) { pOutput[0] = FloatToInt(fInput); }
	BURGER_INLINE void FloatToIntCeil(Int32 *pOutput,float fInput) { pOutput[0] = FloatToIntCeil(fInput); }
	BURGER_INLINE void FloatToIntNearest(Int32 *pOutput,float fInput) { pOutput[0] = FloatToIntNearest(fInput); }
#endif
#elif defined(BURGER_POWERPC) && defined(BURGER_METROWERKS)
	BURGER_INLINE Int32 FloatToIntFloor(register float fInput) { volatile Int32 iResult; fInput = fInput-0.5f; register volatile Int32 *pResult = &iResult; asm { fctiw fInput,fInput; stfiwx fInput,r0,pResult } return iResult; }
	BURGER_INLINE Int32 FloatToInt(register float fInput) { volatile Int32 iResult; register volatile Int32 *pResult = &iResult; asm { fctiwz fInput,fInput; stfiwx fInput,r0,pResult } return iResult; }
	BURGER_INLINE Int32 FloatToIntCeil(register float fInput) { volatile Int32 iResult; fInput = fInput+(0.5f-(1.0f/(65536.0f*256.0f))); register volatile Int32 *pResult = &iResult; asm { fctiw fInput,fInput; stfiwx fInput,r0,pResult } return iResult; }
	BURGER_INLINE Int32 FloatToIntNearest(register float fInput) { volatile Int32 iResult; register volatile Int32 *pResult = &iResult; asm { fctiw fInput,fInput; stfiwx fInput,r0,pResult } return iResult; }
	BURGER_INLINE void FloatToIntFloor(register Int32 *pOutput,register float fInput) { fInput = fInput-0.5f; asm { fctiw fInput,fInput; stfiwx fInput,r0,pOutput } }
	BURGER_INLINE void FloatToInt(register Int32 *pOutput,register float fInput) { asm { fctiwz fInput,fInput; stfiwx fInput,r0,pOutput } }
	BURGER_INLINE void FloatToIntCeil(register Int32 *pOutput,register float fInput) { fInput = fInput+(0.5f-(1.0f/(65536.0f*256.0f))); asm { fctiw fInput,fInput; stfiwx fInput,r0,pOutput } }
	BURGER_INLINE void FloatToIntNearest(register Int32 *pOutput,register float fInput) { asm { fctiw fInput,fInput; stfiwx fInput,r0,pOutput } }
#elif defined(BURGER_X86) && defined(BURGER_METROWERKS)
	BURGER_INLINE Int32 FloatToIntFloor(float fInput) { asm fld DWORD PTR fInput
		asm fadd DWORD PTR [g_fBurgerIntMathNearesttable]
		asm fistp DWORD PTR fInput
		return reinterpret_cast<Int32 *>(&fInput)[0];}
	BURGER_INLINE Int32 FloatToInt(float fInput) { asm fld DWORD PTR fInput
		asm mov eax,fInput
		asm shr eax,31
		asm fadd dword ptr [g_fBurgerIntMathNearesttable+eax*4]
		asm fistp DWORD PTR fInput
		return reinterpret_cast<Int32 *>(&fInput)[0]; }
	BURGER_INLINE Int32 FloatToIntCeil(float fInput) { asm fld DWORD PTR fInput
		asm fadd DWORD PTR [g_fBurgerIntMathNearesttable+4]
		asm fistp DWORD PTR fInput
		return reinterpret_cast<Int32 *>(&fInput)[0]; }
	BURGER_INLINE Int32 FloatToIntNearest(float fInput) { asm fld DWORD PTR fInput
		asm fistp DWORD PTR fInput
		return reinterpret_cast<Int32 *>(&fInput)[0]; }
	BURGER_INLINE void FloatToIntFloor(Int32 *pOutput,float fInput) { asm mov ecx,pOutput
		asm fld DWORD PTR fInput
		asm fadd DWORD PTR [g_fBurgerIntMathNearesttable]
		asm { fistp DWORD PTR [ecx] } }
	BURGER_INLINE void FloatToInt(Int32 *pOutput,float fInput) { asm mov ecx,pOutput
		asm fld DWORD PTR fInput
		asm mov eax,fInput
		asm shr eax,31
		asm fadd dword ptr [g_fBurgerIntMathNearesttable+eax*4]
		asm { fistp DWORD PTR [ecx] } }
	BURGER_INLINE void FloatToIntCeil(Int32 *pOutput,float fInput) { asm mov ecx,pOutput
		asm fld DWORD PTR fInput
		asm fadd DWORD PTR [g_fBurgerIntMathNearesttable+4]
		asm { fistp DWORD PTR [ecx] } }
	BURGER_INLINE void FloatToIntNearest(Int32 *pOutput,float fInput) { asm mov ecx,pOutput
		asm fld DWORD PTR fInput
		asm { fistp DWORD PTR [ecx] } }
#elif defined(BURGER_X86) && defined(BURGER_MSVC)
	BURGER_INLINE Int32 FloatToIntFloor(float fInput) { __asm fld DWORD PTR [fInput]
		__asm fadd DWORD PTR [g_fBurgerIntMathNearesttable]
		__asm fistp DWORD PTR [fInput]
		return reinterpret_cast<Int32 *>(&fInput)[0]; }
	BURGER_INLINE Int32 FloatToInt(float fInput) { __asm fld DWORD PTR [fInput]
		__asm mov eax,[fInput]
		__asm shr eax,31
		__asm fadd dword ptr [g_fBurgerIntMathNearesttable+eax*4]
		__asm fistp DWORD PTR [fInput]
		return reinterpret_cast<Int32 *>(&fInput)[0]; }
	BURGER_INLINE Int32 FloatToIntCeil(float fInput) { __asm fld DWORD PTR [fInput]
		__asm fadd DWORD PTR [g_fBurgerIntMathNearesttable+4]
		__asm fistp DWORD PTR [fInput]
		return reinterpret_cast<Int32 *>(&fInput)[0]; }
	BURGER_INLINE Int32 FloatToIntNearest(float fInput) { __asm fld DWORD PTR [fInput]
		__asm fistp DWORD PTR [fInput]
		return reinterpret_cast<Int32 *>(&fInput)[0]; }
	BURGER_INLINE void FloatToIntFloor(Int32 *pOutput,float fInput) { __asm mov ecx,pOutput
		__asm fld DWORD PTR [fInput]
		__asm fadd DWORD PTR [g_fBurgerIntMathNearesttable]
		__asm fistp DWORD PTR [ecx] }
	BURGER_INLINE void FloatToInt(Int32 *pOutput,float fInput) { __asm mov ecx,pOutput
		__asm fld DWORD PTR [fInput]
		__asm mov eax,[fInput]
		__asm shr eax,31
		__asm fadd dword ptr [g_fBurgerIntMathNearesttable+eax*4]
		__asm fistp DWORD PTR [ecx] }
	BURGER_INLINE void FloatToIntCeil(Int32 *pOutput,float fInput) { __asm mov ecx,pOutput
		__asm fld DWORD PTR [fInput]
		__asm fadd DWORD PTR [g_fBurgerIntMathNearesttable+4]
		__asm fistp DWORD PTR [ecx] }
	BURGER_INLINE void FloatToIntNearest(Int32 *pOutput,float fInput) { __asm mov ecx,pOutput
		__asm fld DWORD PTR [fInput]
		__asm fistp DWORD PTR [ecx] }
#elif defined(BURGER_AMD64) && defined(BURGER_MSVC)
	BURGER_INLINE Int32 FloatToIntFloor(float fInput) { return _mm_cvt_ss2si(_mm_set_ss(fInput+g_fBurgerIntMathNearesttable[0])); }
	BURGER_INLINE Int32 FloatToInt(float fInput) { return static_cast<Int32>(fInput); }
	BURGER_INLINE Int32 FloatToIntCeil(float fInput) { return _mm_cvt_ss2si(_mm_set_ss(fInput+g_fBurgerIntMathNearesttable[1])); }
	BURGER_INLINE Int32 FloatToIntNearest(float fInput) { return _mm_cvt_ss2si(_mm_set_ss(fInput));}
	BURGER_INLINE void FloatToIntFloor(Int32 *pOutput,float fInput) { pOutput[0] = _mm_cvt_ss2si(_mm_set_ss(fInput+g_fBurgerIntMathNearesttable[0])); }
	BURGER_INLINE void FloatToInt(Int32 *pOutput,float fInput) { pOutput[0] = static_cast<Int32>(fInput); }
	BURGER_INLINE void FloatToIntCeil(Int32 *pOutput,float fInput) { pOutput[0] = _mm_cvt_ss2si(_mm_set_ss(fInput+g_fBurgerIntMathNearesttable[1])); }
	BURGER_INLINE void FloatToIntNearest(Int32 *pOutput,float fInput) { pOutput[0] = _mm_cvt_ss2si(_mm_set_ss(fInput)); }
#else
	extern Int32 BURGER_API FloatToIntFloor(float fInput);
	extern Int32 BURGER_API FloatToInt(float fInput);
	extern Int32 BURGER_API FloatToIntCeil(float fInput);
	extern Int32 BURGER_API FloatToIntNearest(float fInput);
	BURGER_INLINE void FloatToIntFloor(Int32 *pOutput,float fInput) { pOutput[0] = FloatToIntFloor(fInput); }
	BURGER_INLINE void FloatToInt(Int32 *pOutput,float fInput) { pOutput[0] = FloatToInt(fInput); }
	BURGER_INLINE void FloatToIntCeil(Int32 *pOutput,float fInput) { pOutput[0] = FloatToIntCeil(fInput); }
	BURGER_INLINE void FloatToIntNearest(Int32 *pOutput,float fInput) { pOutput[0] = FloatToIntNearest(fInput); }
#endif
#if defined(BURGER_WATCOM)
	BURGER_INLINE Fixed32 FloatToFixedFloor(float fInput) { return BurgerFixedMathFromFloatFloor(fInput); }
	BURGER_INLINE Fixed32 FloatToFixed(float fInput) { return BurgerFixedMathFromFloat(fInput); }
	BURGER_INLINE Fixed32 FloatToFixedCeil(float fInput) { return BurgerFixedMathFromFloatCeil(fInput); }
	BURGER_INLINE Fixed32 FloatToFixedNearest(float fInput) { return BurgerFixedMathFromFloatNearest(fInput); }
	BURGER_INLINE void FloatToFixedFloor(Fixed32 *pOutput,float fInput) { BurgerFixedMathFromFloatFloor2(pOutput,fInput); }
	BURGER_INLINE void FloatToFixed(Fixed32 *pOutput,float fInput) { BurgerFixedMathFromFloat2(pOutput,fInput); }
	BURGER_INLINE void FloatToFixedCeil(Fixed32 *pOutput,float fInput) { BurgerFixedMathFromFloatCeil2(pOutput,fInput); }
	BURGER_INLINE void FloatToFixedNearest(Fixed32 *pOutput,float fInput) { BurgerFixedMathFromFloatNearest2(pOutput,fInput); }
#elif defined(BURGER_X86) && defined(BURGER_METROWERKS)
	BURGER_INLINE Fixed32 FloatToFixedFloor(float fInput) { asm fld DWORD PTR fInput
		asm fmul DWORD PTR [g_fBurgerMath65536]
		asm fadd DWORD PTR [g_fBurgerIntMathNearesttable]
		asm fistp DWORD PTR fInput
		return reinterpret_cast<Fixed32 *>(&fInput)[0];}
	BURGER_INLINE Fixed32 FloatToFixed(float fInput) { asm fld DWORD PTR fInput
		asm fmul DWORD PTR [g_fBurgerMath65536]
		asm mov eax,fInput
		asm shr eax,31
		asm fadd dword ptr [g_fBurgerIntMathNearesttable+eax*4]
		asm fistp DWORD PTR fInput
		return reinterpret_cast<Fixed32 *>(&fInput)[0]; }
	BURGER_INLINE Fixed32 FloatToFixedCeil(float fInput) { asm fld DWORD PTR fInput
		asm fmul DWORD PTR [g_fBurgerMath65536]
		asm fadd DWORD PTR [g_fBurgerIntMathNearesttable+4]
		asm fistp DWORD PTR fInput
		return reinterpret_cast<Fixed32 *>(&fInput)[0]; }
	BURGER_INLINE Fixed32 FloatToFixedNearest(float fInput) { asm fld DWORD PTR fInput
		asm fmul DWORD PTR [g_fBurgerMath65536]
		asm fistp DWORD PTR fInput
		return reinterpret_cast<Fixed32 *>(&fInput)[0]; }
	BURGER_INLINE void FloatToFixedFloor(Fixed32 *pOutput,float fInput) { asm mov ecx,pOutput
		asm fld DWORD PTR fInput
		asm fmul DWORD PTR [g_fBurgerMath65536]
		asm fadd DWORD PTR [g_fBurgerIntMathNearesttable]
		asm { fistp DWORD PTR [ecx] } }
	BURGER_INLINE void FloatToFixed(Fixed32 *pOutput,float fInput) { asm mov ecx,pOutput
		asm fld DWORD PTR fInput
		asm fmul DWORD PTR [g_fBurgerMath65536]
		asm mov eax,DWORD PTR [fInput]
		asm shr eax,31
		asm fadd dword ptr [g_fBurgerIntMathNearesttable+eax*4]
		asm { fistp DWORD PTR [ecx] } }
	BURGER_INLINE void FloatToFixedCeil(Fixed32 *pOutput,float fInput) { asm mov ecx,pOutput
		asm fld DWORD PTR fInput
		asm fmul DWORD PTR [g_fBurgerMath65536]
		asm fadd DWORD PTR [g_fBurgerIntMathNearesttable+4]
		asm { fistp DWORD PTR [ecx] } }
	BURGER_INLINE void FloatToFixedNearest(Fixed32 *pOutput,float fInput) { asm mov ecx,pOutput
		asm fld DWORD PTR fInput
		asm fmul DWORD PTR [g_fBurgerMath65536]
		asm { fistp DWORD PTR [ecx] } }
#elif defined(BURGER_X86) && defined(BURGER_MSVC)
	BURGER_INLINE Int32 FloatToFixedFloor(float fInput) { __asm fld DWORD PTR [fInput]
		__asm fmul DWORD PTR [g_fBurgerMath65536]
		__asm fadd DWORD PTR [g_fBurgerIntMathNearesttable]
		__asm fistp DWORD PTR [fInput]
		return reinterpret_cast<Fixed32 *>(&fInput)[0]; }
	BURGER_INLINE Int32 FloatToFixed(float fInput) { __asm fld DWORD PTR [fInput]
		__asm fmul DWORD PTR [g_fBurgerMath65536]
		__asm mov eax,[fInput]
		__asm shr eax,31
		__asm fadd dword ptr [g_fBurgerIntMathNearesttable+eax*4]
		__asm fistp DWORD PTR [fInput]
		return reinterpret_cast<Fixed32 *>(&fInput)[0]; }
	BURGER_INLINE Int32 FloatToFixedCeil(float fInput) { __asm fld DWORD PTR [fInput]
		__asm fmul DWORD PTR [g_fBurgerMath65536]
		__asm fadd DWORD PTR [g_fBurgerIntMathNearesttable+4]
		__asm fistp DWORD PTR [fInput]
		return reinterpret_cast<Fixed32 *>(&fInput)[0]; }
	BURGER_INLINE Int32 FloatToFixedNearest(float fInput) { __asm fld DWORD PTR [fInput]
		__asm fmul DWORD PTR [g_fBurgerMath65536]
		__asm fistp DWORD PTR [fInput]
		return reinterpret_cast<Fixed32 *>(&fInput)[0]; }
	BURGER_INLINE void FloatToFixedFloor(Fixed32 *pOutput,float fInput) { __asm mov ecx,pOutput
		__asm fld DWORD PTR [fInput]
		__asm fmul DWORD PTR [g_fBurgerMath65536]
		__asm fadd DWORD PTR [g_fBurgerIntMathNearesttable]
		__asm fistp DWORD PTR [ecx] }
	BURGER_INLINE void FloatToFixed(Fixed32 *pOutput,float fInput) { __asm mov ecx,pOutput
		__asm fld DWORD PTR [fInput]
		__asm fmul DWORD PTR [g_fBurgerMath65536]
		__asm mov eax,[fInput]
		__asm shr eax,31
		__asm fadd dword ptr [g_fBurgerIntMathNearesttable+eax*4]
		__asm fistp DWORD PTR [ecx] }
	BURGER_INLINE void FloatToFixedCeil(Fixed32 *pOutput,float fInput) { __asm mov ecx,pOutput
		__asm fld DWORD PTR [fInput]
		__asm fmul DWORD PTR [g_fBurgerMath65536]
		__asm fadd DWORD PTR [g_fBurgerIntMathNearesttable+4]
		__asm fistp DWORD PTR [ecx] }
	BURGER_INLINE void FloatToFixedNearest(Fixed32 *pOutput,float fInput) { __asm mov ecx,pOutput
		__asm fld DWORD PTR [fInput]
		__asm fmul DWORD PTR [g_fBurgerMath65536]
		__asm fistp DWORD PTR [ecx] }
#else
	BURGER_INLINE Fixed32 FloatToFixedFloor(float fInput) { return static_cast<Fixed32>(FloatToIntFloor(fInput*65536.0f)); }
	BURGER_INLINE Fixed32 FloatToFixed(float fInput) { return static_cast<Fixed32>(FloatToInt(fInput*65536.0f)); }
	BURGER_INLINE Fixed32 FloatToFixedCeil(float fInput) { return static_cast<Fixed32>(FloatToIntCeil(fInput*65536.0f)); }
	BURGER_INLINE Fixed32 FloatToFixedNearest(float fInput) { return static_cast<Fixed32>(FloatToIntNearest(fInput*65536.0f)); }
	BURGER_INLINE void FloatToFixedFloor(Fixed32 *pOutput,float fInput) { FloatToIntFloor(reinterpret_cast<Int32*>(pOutput),fInput*65536.0f); }
	BURGER_INLINE void FloatToFixed(Fixed32 *pOutput,float fInput) { FloatToInt(reinterpret_cast<Int32*>(pOutput),fInput*65536.0f); }
	BURGER_INLINE void FloatToFixedCeil(Fixed32 *pOutput,float fInput) { FloatToIntCeil(reinterpret_cast<Int32*>(pOutput),fInput*65536.0f); }
	BURGER_INLINE void FloatToFixedNearest(Fixed32 *pOutput,float fInput) { FloatToIntNearest(reinterpret_cast<Int32*>(pOutput),fInput*65536.0f); }
#endif
#if !defined(BURGER_ARM) || defined(DOXYGEN)
	BURGER_INLINE Int32 Abs(Int32 iInput) { Int32 iMask = (iInput>>31); return (iInput^iMask)-iMask; }
	BURGER_INLINE Int64 Abs(Int64 iInput) { Int64 iMask = (iInput>>63); return (iInput^iMask)-iMask; }
	BURGER_INLINE Int32 ClampZero(Int32 iInput) { return (~(iInput>>31))&iInput; }
	BURGER_INLINE Int64 ClampZero(Int64 iInput) { return (~(iInput>>63))&iInput; }
#else
	BURGER_INLINE Int32 Abs(Int32 iInput) { if (iInput<0) { iInput=-iInput; } return iInput; }
	BURGER_INLINE Int64 Abs(Int64 iInput) { if (iInput<0) { iInput=-iInput; } return iInput; }
	BURGER_INLINE Int32 ClampZero(Int32 iInput) { if (iInput<0) { iInput=0; } return iInput; }
	BURGER_INLINE Int64 ClampZero(Int64 iInput) { if (iInput<0) { iInput=0; } return iInput; }
#endif
	BURGER_INLINE Int32 Min(Int32 iA,Int32 iB) { return ((iA < iB) ? iA : iB); }
	BURGER_INLINE Int64 Min(Int64 iA,Int64 iB) { return ((iA < iB) ? iA : iB); }
	BURGER_INLINE Word32 Min(Word32 uA,Word32 uB) { return ((uA < uB) ? uA : uB); }
	BURGER_INLINE Word64 Min(Word64 uA,Word64 uB) { return ((uA < uB) ? uA : uB); }
	BURGER_INLINE Int32 Max(Int32 iA,Int32 iB) { return ((iA > iB) ? iA : iB); }
	BURGER_INLINE Int64 Max(Int64 iA,Int64 iB) { return ((iA > iB) ? iA : iB); }
	BURGER_INLINE Word32 Max(Word32 uA,Word32 uB) { return ((uA > uB) ? uA : uB); }
	BURGER_INLINE Word64 Max(Word64 uA,Word64 uB) { return ((uA > uB) ? uA : uB); }
	BURGER_INLINE Int32 Clamp(Int32 iInput,Int32 iMin,Int32 iMax) { iInput = Max(iInput,iMin); return Min(iInput,iMax); }
	BURGER_INLINE Int64 Clamp(Int64 iInput,Int64 iMin,Int64 iMax) { iInput = Max(iInput,iMin); return Min(iInput,iMax); }
	BURGER_INLINE Word32 Clamp(Word32 uInput,Word32 uMin,Word32 uMax) { uInput = Max(uInput,uMin); return Min(uInput,uMax); }
	BURGER_INLINE Word64 Clamp(Word64 uInput,Word64 uMin,Word64 uMax) { uInput = Max(uInput,uMin); return Min(uInput,uMax); }
#if defined(BURGER_WATCOM)
	BURGER_INLINE Fixed32 FixedMultiply(Fixed32 fInput1,Fixed32 fInput2) { return BurgerFixedMathMultiply(fInput1,fInput2); }
	BURGER_INLINE Fixed32 FixedDivide(Fixed32 fInputNumerator,Fixed32 fInputDenominator) { return BurgerFixedMathDivide(fInputNumerator,fInputDenominator); }
	BURGER_INLINE Fixed32 FixedReciprocal(Fixed32 fInput) { return BurgerFixedMathReciprocal(fInput); }
#elif defined(BURGER_X86) && defined(BURGER_METROWERKS)
	BURGER_INLINE Fixed32 FixedMultiply(Fixed32 fInput1,Fixed32 fInput2) { asm mov eax,fInput1
		asm imul fInput2
		asm shrd eax,edx,16
		asm mov fInput1,eax
		return fInput1; }
	BURGER_INLINE Fixed32 FixedDivide(Fixed32 fInputNumerator,Fixed32 fInputDenominator) { asm mov eax,fInputNumerator
		asm mov edx,fInputNumerator
		asm shl eax,16
		asm sar edx,16
		asm idiv fInputDenominator
		asm mov fInputNumerator,eax
		return fInputNumerator; }
	BURGER_INLINE Fixed32 FixedReciprocal(Fixed32 fInput) { asm mov ecx,fInput
		asm cmp ecx,-1
		asm mov eax,080000000H
		asm je Done
		asm dec eax
		asm cmp ecx,2
		asm jb Done
		asm xor eax,eax
		asm mov edx,1
		asm idiv ecx
	Done:
		asm mov fInput,eax
		return fInput; }
#elif defined(BURGER_X86) && defined(BURGER_MSVC)
	BURGER_INLINE Fixed32 FixedMultiply(Fixed32 fInput1,Fixed32 fInput2) { __asm mov eax,fInput1
		__asm mov edx,fInput2
		__asm imul edx
		__asm shrd eax,edx,16
		__asm mov fInput1,eax
		return fInput1; }
	BURGER_INLINE Fixed32 FixedDivide(Fixed32 fInputNumerator,Fixed32 fInputDenominator) { __asm mov eax,fInputNumerator
		__asm mov ebx,fInputDenominator
		__asm mov edx,eax
		__asm shl eax,16
		__asm sar edx,16
		__asm idiv ebx
		__asm mov fInputNumerator,eax
		return fInputNumerator; }
	BURGER_INLINE Fixed32 FixedReciprocal(Fixed32 fInput) {
		if (fInput==-1) {		// Note: Visual C does not like branches in inline asm
			fInput=0x80000000;
		} else if (static_cast<Word32>(fInput)<2) {
			fInput=0x7FFFFFFF;
		} else {
			__asm mov ecx,fInput
			__asm xor eax,eax
			__asm mov edx,1
			__asm idiv ecx
			__asm mov fInput,eax
		}
		return fInput;
	}
#elif defined(BURGER_POWERPC) || defined(BURGER_64BITCPU) && !defined(DOXYGEN)
	BURGER_INLINE Fixed32 FixedMultiply(Fixed32 fInput1,Fixed32 fInput2) { return static_cast<Fixed32>(((static_cast<Int64>(fInput1)*static_cast<Int64>(fInput2))>>16)&0xFFFFFFFF); }
	BURGER_INLINE Fixed32 FixedDivide(Fixed32 fInputNumerator,Fixed32 fInputDenominator) { return static_cast<Fixed32>((static_cast<Int64>(fInputNumerator)<<16)/fInputDenominator); }
	BURGER_INLINE Fixed32 FixedReciprocal(Fixed32 fInput) {
		if (fInput==-1) {
			fInput = 0x80000000;
		} else if (static_cast<Word32>(fInput)<2) {
			fInput = 0x7FFFFFFF;
		} else {
			fInput = static_cast<Fixed32>(0x100000000LL/static_cast<Int64>(fInput));
		}
		return fInput;
	}
#else
	extern Fixed32 BURGER_API FixedMultiply(Fixed32 fInput1,Fixed32 fInput2);
	extern Fixed32 BURGER_API FixedDivide(Fixed32 fInputNumerator,Fixed32 fInputDenominator);
	extern Fixed32 BURGER_API FixedReciprocal(Fixed32 fInput);
#endif
	extern Word32 BURGER_API Sqrt(Word32 uInput);
	extern Word32 BURGER_API SqrtFixedToWord32(Fixed32 fInput);
	extern Fixed32 BURGER_API Sqrt(Fixed32 uInput);
#if defined(BURGER_MSVC) || defined(BURGER_WATCOM)
	BURGER_INLINE Word32 RotateLeft(Word32 uInput,Word uShiftCount) { return static_cast<Word32>(_rotl(uInput,uShiftCount)); }
	BURGER_INLINE Word32 RotateRight(Word32 uInput,Word uShiftCount) { return static_cast<Word32>(_rotr(uInput,uShiftCount)); }
#elif (defined(BURGER_METROWERKS) && (defined(BURGER_X86) || defined(BURGER_68K)))
	BURGER_INLINE Word32 RotateLeft(Word32 uInput,Word uShiftCount) { return static_cast<Word32>(__rol(uInput,uShiftCount)); }
	BURGER_INLINE Word32 RotateRight(Word32 uInput,Word uShiftCount) { return static_cast<Word32>(__ror(uInput,uShiftCount)); }
#elif (defined(BURGER_METROWERKS) && defined(BURGER_POWERPC))
	BURGER_INLINE Word32 RotateLeft(Word32 uInput,Word uShiftCount) { return static_cast<Word32>(__builtin___rotate_left32(uInput,static_cast<int>(uShiftCount))); }
	BURGER_INLINE Word32 RotateRight(Word32 uInput,Word uShiftCount) { return static_cast<Word32>(__builtin___rotate_right32(uInput,static_cast<int>(uShiftCount))); }
#elif defined(BURGER_VITA)
	BURGER_INLINE Word32 RotateLeft(Word32 uInput,Word uShiftCount) { return __builtin_rol(uInput,static_cast<Word32>(uShiftCount)); }
	BURGER_INLINE Word32 RotateRight(Word32 uInput,Word uShiftCount) { return __builtin_ror(uInput,static_cast<Word32>(uShiftCount)); }
#else
	BURGER_INLINE Word32 RotateLeft(Word32 uInput,Word uShiftCount) { return ((uInput<<uShiftCount) | (uInput>>(32-uShiftCount))); }
	BURGER_INLINE Word32 RotateRight(Word32 uInput,Word uShiftCount) { return ((uInput>>uShiftCount) | (uInput<<(32-uShiftCount))); }
#endif
#if defined(BURGER_MSVC)
	BURGER_INLINE Word64 RotateLeft(Word64 uInput,Word uShiftCount) { return _rotl64(uInput,uShiftCount); }
	BURGER_INLINE Word64 RotateRight(Word64 uInput,Word uShiftCount) { return _rotr64(uInput,uShiftCount); }
#else
	BURGER_INLINE Word64 RotateLeft(Word64 uInput,Word uShiftCount) { return ((uInput<<uShiftCount) | (uInput>>(64-uShiftCount))); }
	BURGER_INLINE Word64 RotateRight(Word64 uInput,Word uShiftCount) { return ((uInput>>uShiftCount) | (uInput<<(64-uShiftCount))); }
#endif
}
namespace Burger {
#define	BURGER_PI 3.1415926535897932384626	///< Pretty accurate, eh?
typedef Word8 Float80Bit[10];				///< 80 bit float (Extended)
struct Word32ToFloat {
	union {
		Word32 w;		///< Value in binary
		float f;		///< Value as a 32 bit float
	};
	BURGER_INLINE operator float() const { return f; }
=======
struct FixedMatrix4D_t;
struct Matrix4D_t {
	Vector4D_t x;	///< 32 bit floating point X row for the 4D Matrix
	Vector4D_t y;	///< 32 bit floating point Y row for the 4D Matrix
	Vector4D_t z;	///< 32 bit floating point Z row for the 4D Matrix
	Vector4D_t w;	///< 32 bit floating point W row for the 4D Matrix
	void BURGER_API Zero(void);
	void BURGER_API Identity(void);
	void BURGER_API Set(const Matrix4D_t *pInput);
	void BURGER_API Set(const FixedMatrix4D_t *pInput);
	void BURGER_API SetYaw(float fYaw);
	void BURGER_API SetPitch(float fPitch);
	void BURGER_API SetRoll(float fRoll);
	void BURGER_API SetYXZ(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetYZX(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetXYZ(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetXZY(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetZYX(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetZXY(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetTranslate(float fX,float fY,float fZ);
	void BURGER_API SetFromQuaternion(const Vector4D_t *pInput);
	void BURGER_API TransposeSetYaw(float fYaw);
	void BURGER_API TransposeSetPitch(float fPitch);
	void BURGER_API TransposeSetRoll(float fRoll);
	void BURGER_API TransposeSetYXZ(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetYZX(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetXYZ(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetXZY(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetZYX(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetZXY(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetFromQuaternion(const Vector4D_t *pInput);
	void BURGER_API SetScale(float fX,float fY,float fZ);
	void BURGER_API SetScale(float fX,float fY,float fZ,float fW);
	void BURGER_API SetFrustum(float fLeft,float fRight,float fBottom,float fTop,float fNear,float fFar);
	void BURGER_API TransposeSetFrustum(float fLeft,float fRight,float fBottom,float fTop,float fNear,float fFar);
	void BURGER_API SetOrtho(float fLeft,float fRight,float fBottom,float fTop,float fNear,float fFar);
	void BURGER_API TransposeSetOrtho(float fLeft,float fRight,float fBottom,float fTop,float fNear,float fFar);
	void BURGER_API Transpose(void);
	void BURGER_API Transpose(const Matrix4D_t *pInput);
	void BURGER_API Multiply(float fInput);
	void BURGER_API Multiply(const Matrix4D_t *pInput,float fInput);
	void BURGER_API Multiply3x3(float fInput);
	void BURGER_API Multiply3x3(const Matrix4D_t *pInput,float fInput);
	void BURGER_API GetXRow(Vector3D_t *pOutput) const;
	void BURGER_API GetXRow(Vector4D_t *pOutput) const;
	void BURGER_API GetYRow(Vector3D_t *pOutput) const;
	void BURGER_API GetYRow(Vector4D_t *pOutput) const;
	void BURGER_API GetZRow(Vector3D_t *pOutput) const;
	void BURGER_API GetZRow(Vector4D_t *pOutput) const;
	void BURGER_API GetWRow(Vector3D_t *pOutput) const;
	void BURGER_API GetWRow(Vector4D_t *pOutput) const;
	void BURGER_API GetXColumn(Vector3D_t *pOutput) const;
	void BURGER_API GetXColumn(Vector4D_t *pOutput) const;
	void BURGER_API GetYColumn(Vector3D_t *pOutput) const;
	void BURGER_API GetYColumn(Vector4D_t *pOutput) const;
	void BURGER_API GetZColumn(Vector3D_t *pOutput) const;
	void BURGER_API GetZColumn(Vector4D_t *pOutput) const;
	void BURGER_API GetWColumn(Vector3D_t *pOutput) const;
	void BURGER_API GetWColumn(Vector4D_t *pOutput) const;
	void BURGER_API SetXRow(const Vector3D_t *pInput);
	void BURGER_API SetXRow(const Vector4D_t *pInput);
	void BURGER_API SetYRow(const Vector3D_t *pInput);
	void BURGER_API SetYRow(const Vector4D_t *pInput);
	void BURGER_API SetZRow(const Vector3D_t *pInput);
	void BURGER_API SetZRow(const Vector4D_t *pInput);
	void BURGER_API SetWRow(const Vector3D_t *pInput);
	void BURGER_API SetWRow(const Vector4D_t *pInput);
	void BURGER_API SetXColumn(const Vector3D_t *pInput);
	void BURGER_API SetXColumn(const Vector4D_t *pInput);
	void BURGER_API SetYColumn(const Vector3D_t *pInput);
	void BURGER_API SetYColumn(const Vector4D_t *pInput);
	void BURGER_API SetZColumn(const Vector3D_t *pInput);
	void BURGER_API SetZColumn(const Vector4D_t *pInput);
	void BURGER_API SetWColumn(const Vector3D_t *pInput);
	void BURGER_API SetWColumn(const Vector4D_t *pInput);
	void BURGER_API Transform(Vector3D_t *pInput) const;
	void BURGER_API Transform(Vector4D_t *pInput) const;
	void BURGER_API Transform(Vector3D_t *pOutput,const Vector3D_t *pInput) const;
	void BURGER_API Transform(Vector4D_t *pOutput,const Vector4D_t *pInput) const;
	void BURGER_API TransposeTransform(Vector3D_t *pInput) const;
	void BURGER_API TransposeTransform(Vector4D_t *pInput) const;
	void BURGER_API TransposeTransform(Vector3D_t *pOutput,const Vector3D_t *pInput) const;
	void BURGER_API TransposeTransform(Vector4D_t *pOutput,const Vector4D_t *pInput) const;
	void BURGER_API Transform3x3(Vector3D_t *pInput) const;
	void BURGER_API Transform3x3(Vector3D_t *pOutput,const Vector3D_t *pInput) const;
	void BURGER_API TransposeTransform3x3(Vector3D_t *pInput) const;
	void BURGER_API TransposeTransform3x3(Vector3D_t *pOutput,const Vector3D_t *pInput) const;
>>>>>>> 8cfb6bc... Updated makeprojects to auto-generate iOS projects under XCode 5.x. iOS binaries are "fat", meaning they have armv7, armv7s, arm64, i386 and x86_64 binaries so it works both on a native device and on the simulators
};
struct Word64ToDouble {
	union {
		Word64 w;		///< Value in binary
		double d;		///< Value as a 64 bit float
	};
	BURGER_INLINE operator double() const { return d; }
};
struct Vector_128Float32 {
	union {
		float BURGER_ALIGN(f[4],16);		///< Value as 4 32 bit floats
		Vector_128 v;	///< Value as a 128 bit vector
	};
	BURGER_INLINE operator Vector_128() const { return v; }
};
struct Vector_128Float64 {
	union {
		double BURGER_ALIGN(d[2],16);		///< Value as 2 64 bit floats
		Vector_128 v;	///< Value as a 128 bit vector
	};
	BURGER_INLINE operator Vector_128() const { return v; }
};
struct Vector_128Int32 {
	union {
		Int32 BURGER_ALIGN(i[4],16);		///< Value as 4 signed 32 bit integers
		Vector_128 v;	///< Value as a 128 bit vector
	};
	BURGER_INLINE operator Vector_128() const { return v; }
};
struct Vector_128Word64 {
	union {
		Word64 BURGER_ALIGN(u[2],16);		///< Value as 2 unsigned 64 bit integers
		Vector_128 v;	///< Value as a 128 bit vector
	};
	BURGER_INLINE operator Vector_128() const { return v; }
};
struct Vector_128Word32 {
	union {
		Word32 BURGER_ALIGN(u[4],16);		///< Value as 4 unsigned 32 bit integers
		Vector_128 v;	///< Value as a 128 bit vector
	};
	BURGER_INLINE operator Vector_128() const { return v; }
};
struct Vector_128Word8 {
	union {
		Word8 BURGER_ALIGN(u[16],16);		///< Value as 16 unsigned 8 bit integers
		Vector_128 v;	///< Value as a 128 bit vector
	};
	BURGER_INLINE operator Vector_128() const { return v; }
};
struct Vector_128Word16 {
	union {
		Word16 BURGER_ALIGN(u[8],16);		///< Value as 8 unsigned 16 bit integers
		Vector_128 v;	///< Value as a 128 bit vector
	};
	BURGER_INLINE operator Vector_128() const { return v; }
};
}
#if defined(BURGER_PS4)
extern "C" float fabsf(float);
extern "C" double fabs(double);
extern "C" float sqrtf(float);
extern "C" double sqrt(double);
#elif defined(BURGER_MACOSX) || (defined(BURGER_IOS) && (defined(BURGER_X86) || defined(BURGER_AMD64)))
extern "C" float sqrtf(float);
extern "C" double sqrt(double);
#if !defined(BURGER_METROWERKS)
extern "C" float fabsf(float);
extern "C" double fabs(double);
#endif
#endif
namespace Burger {
	extern const Word64ToDouble g_dOne;			///< Constant for 1.0 in the double format.
	extern const Word64ToDouble g_dHalf;		///< Constant for 0.5 in the double format.
	extern const Word64ToDouble g_dInf;			///< Constant for Infinity in the double format.
	extern const Word64ToDouble g_dNan;			///< Constant for signaling Not a Number (NaN) in the double format.
	extern const Word64ToDouble g_dQNan;		///< Constant for non signaling Not a Number (Nan) in the double format.
	extern const Word64ToDouble g_dMin;			///< Constant for the smallest number (Non-zero) in the double format.
	extern const Word64ToDouble g_dMax;			///< Constant for the largest number in the double format.
	extern const Word64ToDouble g_dEpsilon;		///< Constant for Epsilon in the double format.
	extern const Word64ToDouble g_dQuarterPi;	///< Constant for Pi*0.25 in the double format.
	extern const Word64ToDouble g_dHalfPi;		///< Constant for Pi*0.5 in the double format.
	extern const Word64ToDouble g_dPi;			///< Constant for Pi in the double format.
	extern const Word64ToDouble g_dPi2;			///< Constant for Pi*2 in the double format.
	extern const Word64ToDouble g_dPi4;			///< Constant for Pi*4 in the double format.
	extern const Word64ToDouble g_dReciprocalHalfPi;	///< Constant for 1/(Pi*0.5) in the double format.
	extern const Word64ToDouble g_dReciprocalPi;		///< Constant for 1/Pi in the double format.
	extern const Word64ToDouble g_dReciprocalPi2;		///< Constant for 1/(Pi*2) in the double format.
	extern const Word64ToDouble g_dRadiansToDegrees;	///< Constant for 180/Pi in the double format.
	extern const Word64ToDouble g_dDegreesToRadians;	///< Constant for Pi/180 in the double format.
	extern const Word32ToFloat g_fOne;			///< Constant for 1.0f in the float format.
	extern const Word32ToFloat g_fHalf;			///< Constant for 0.5f in the float format.
	extern const Word32ToFloat g_fInf;			///< Constant for Infinity in the float format.
	extern const Word32ToFloat g_fNan;			///< Constant for signaling Not a Number (NaN) in the float format.
	extern const Word32ToFloat g_fQNan;			///< Constant for non signaling Not a Number (Nan) in the float format.
	extern const Word32ToFloat g_fMin;			///< Constant for smallest number (Non-zero) in the float format.
	extern const Word32ToFloat g_fMax;			///< Constant for largest number in the float format.
	extern const Word32ToFloat g_fEpsilon;		///< Constant for Epsilon in the float format.
	extern const Word32ToFloat g_fQuarterPi;	///< Constant for Pi*0.25f in the float format.
	extern const Word32ToFloat g_fHalfPi;		///< Constant for Pi*0.5f in the float format.
	extern const Word32ToFloat g_fPi;			///< Constant for Pi in the float format.
	extern const Word32ToFloat g_fPi2;			///< Constant for Pi*2 in the float format.
	extern const Word32ToFloat g_fPi4;			///< Constant for Pi*4 in the float format.
	extern const Word32ToFloat g_fReciprocalHalfPi;	///< Constant for 1/(Pi*0.5f) in the float format.
	extern const Word32ToFloat g_fReciprocalPi;		///< Constant for 1/Pi in the float format.
	extern const Word32ToFloat g_fReciprocalPi2;	///< Constant for 1/(Pi*2.0f) in the float format.
	extern const Word32ToFloat g_fRadiansToDegrees;	///< Constant for 180/Pi in the float format.
	extern const Word32ToFloat g_fDegreesToRadians;	///< Constant for Pi/180 in the float format.
#if defined(BURGER_X86) || defined(DOXYGEN)
	enum e8087Precision {
		PRECISION24=0,	///< Use 24 bit / float precision  (DirectX default)
		PRECISION56=2,	///< Use 56 bit / double precision
		PRECISION64=3	///< Use 64 bit / long double precision (Power up default)
	};
	extern e8087Precision BURGER_API Set8087Precision(e8087Precision eInput);
	enum e8087Rounding {
		ROUNDTONEAREST=0,	///< Use round to nearest integer
		ROUNDDOWN=1,		///< Use Floor() rounding
		ROUNDUP=2,			///< Use Ceil() rounding
		ROUNDTRUNCATE=3		///< Use fraction truncation rounding
	};
	extern e8087Rounding BURGER_API Set8087Rounding(e8087Rounding eInput);
#endif
	float BURGER_INLINE Sqr(float fInput) { return fInput*fInput; }
	double BURGER_INLINE Sqr(double dInput) { return dInput*dInput; }
#if defined(BURGER_WATCOM)
	float BURGER_INLINE Abs(float fInput) { return static_cast<float>(::std::fabs(fInput)); }
	double BURGER_INLINE Abs(double dInput) { return ::std::fabs(dInput); }
	float BURGER_INLINE Sqrt(float fInput) { return static_cast<float>(::std::sqrt(fInput)); }
	double BURGER_INLINE Sqrt(double dInput) { return ::std::sqrt(dInput); }
#elif defined(BURGER_XBOX360) && !defined(DOXYGEN)
	float BURGER_INLINE Abs(float fInput) { return static_cast<float>(fabs(fInput)); }
	double BURGER_INLINE Abs(double dInput) { return fabs(dInput); }
	float BURGER_INLINE Sqrt(float fInput) { return __fsqrts(fInput); }
	double BURGER_INLINE Sqrt(double dInput) { return __fsqrt(dInput); }
#elif defined(BURGER_PS4) && !defined(DOXYGEN)
	float BURGER_INLINE Abs(float fInput) { return fabsf(fInput); }
	double BURGER_INLINE Abs(double dInput) { return fabs(dInput); }
	float BURGER_INLINE Sqrt(float fInput) { return sqrtf(fInput); }
	double BURGER_INLINE Sqrt(double dInput) { return sqrt(dInput); }
#elif defined(BURGER_VITA) && !defined(DOXYGEN)
	float BURGER_INLINE Abs(float fInput) { return __builtin_fabsf(fInput); }
	double BURGER_INLINE Abs(double dInput) { return __builtin_fabs(dInput); }
	float BURGER_INLINE Sqrt(float fInput) { return __builtin_sqrtf(fInput); }
	double BURGER_INLINE Sqrt(double dInput) { return __builtin_sqrt(dInput); }
#elif defined(BURGER_METROWERKS) && defined(BURGER_POWERPC)
	float BURGER_INLINE Abs(float fInput) { return __fabsf(fInput); }
	double BURGER_INLINE Abs(double dInput) { return __fabs(dInput); }
#if defined(BURGER_MACOSX)
	float BURGER_INLINE Sqrt(float fInput) { return sqrtf(fInput); }
#else
	float BURGER_INLINE Sqrt(float fInput) { return static_cast<float>(sqrt(fInput)); }
#endif
	double BURGER_INLINE Sqrt(double dInput) { return sqrt(dInput); }
#elif defined(BURGER_METROWERKS) && defined(BURGER_X86)
#if __has_intrinsic(__builtin_fabsf)
	float BURGER_INLINE Abs(float fInput) { return ::std::__builtin_fabsf(fInput); }
#else
	float BURGER_INLINE Abs(float fInput) { asm fld fInput
		asm fabs
		asm fstp fInput
	return fInput; }
#endif
#if __has_intrinsic(__builtin_fabs)
	double BURGER_INLINE Abs(double dInput) { return ::std::__builtin_fabs(dInput); }
#else
	double BURGER_INLINE Abs(double dInput) { asm fld dInput
		asm fabs
		asm fstp dInput
	return dInput; }
#endif
#if __has_intrinsic(__builtin_sqrt)
	float BURGER_INLINE Sqrt(float fInput) { return static_cast<float>(::std::__builtin_sqrt(fInput)); }
	double BURGER_INLINE Sqrt(double dInput) { return ::std::__builtin_sqrt(dInput); }
#else
	float BURGER_INLINE Sqrt(float fInput) { asm fld fInput
		asm fsqrt
		asm fstp fInput
	return fInput; }
	double BURGER_INLINE Sqrt(double dInput) { asm fld dInput
		asm fsqrt
		asm fstp dInput
	return dInput; }
#endif
#elif (defined(BURGER_X86) || defined(BURGER_AMD64) || (defined(BURGER_MACOSX) && !defined(BURGER_METROWERKS))) && !defined(DOXYGEN)
	float BURGER_INLINE Abs(float fInput) { return static_cast<float>(fabs(fInput)); }
	double BURGER_INLINE Abs(double dInput) { return fabs(dInput); }
	float BURGER_INLINE Sqrt(float fInput) { return static_cast<float>(sqrt(static_cast<double>(fInput))); }
	double BURGER_INLINE Sqrt(double dInput) { return sqrt(dInput); }
#else
	extern float BURGER_API Abs(float fInput);
	extern double BURGER_API Abs(double dInput);
	extern float BURGER_API Sqrt(float fInput);
	extern double BURGER_API Sqrt(double dInput);
#endif
	float BURGER_INLINE IntToFloat(Int32 iInput) { return static_cast<float>(iInput); }
	float BURGER_INLINE IntToFloat(const Int32 *pInput) { return static_cast<float>(pInput[0]); }
	void BURGER_INLINE IntToFloat(float *pOutput,Int32 iInput) { pOutput[0] = static_cast<float>(iInput); }
	float BURGER_INLINE FixedToFloat(Fixed32 fInput) { return static_cast<float>(fInput)*(1.0f/65536.0f); }
	float BURGER_INLINE FixedToFloat(const Fixed32 *pInput) { return static_cast<float>(pInput[0])*(1.0f/65536.0f); }
	void BURGER_INLINE FixedToFloat(float *pOutput,Fixed32 fInput) { pOutput[0] = static_cast<float>(fInput)*(1.0f/65536.0f); }
#if defined(BURGER_XBOX360) && !defined(DOXYGEN)
	void BURGER_INLINE IntToFloat(float *pOutput,const Int32 *pInput) {
		__vector4 vTemp = __lvlx(pInput,0);	// Load in VMX128
		vTemp = __vcfsx(vTemp,0);			// Convert
		vTemp = __vspltw(vTemp,0);			// Splat
		__stvewx(vTemp,pOutput,0);			// Store 32 bit
	}
	void BURGER_INLINE FixedToFloat(float *pOutput,const Fixed32 *pInput) {
		__vector4 vTemp = __lvlx(pInput,0);	// Load in VMX128
		vTemp = __vcfsx(vTemp,16);		// Use 16.16 fixed point conversion
		vTemp = __vspltw(vTemp,0);		// Splat
		__stvewx(vTemp,pOutput,0);		// Store 32 bit
	}
#else
	void BURGER_INLINE IntToFloat(float *pOutput,const Int32 *pInput) { pOutput[0] = static_cast<float>(pInput[0]); }
	void BURGER_INLINE FixedToFloat(float *pOutput,const Fixed32 *pInput) { pOutput[0] = static_cast<float>(pInput[0])*(1.0f/65536.0f); }
#endif
	BURGER_INLINE float Interpolate(float fFrom,float fTo,float fFactor) { return ((fTo - fFrom) * fFactor) + fFrom; }
	BURGER_INLINE double Interpolate(double dFrom,double dTo,double dFactor) { return ((dTo - dFrom) * dFactor) + dFrom; }
	BURGER_INLINE float Square(float fInput) { return fInput*fInput; }
	BURGER_INLINE double Square(double dInput) { return dInput*dInput; }
#if defined(BURGER_METROWERKS) && defined(BURGER_POWERPC)
	BURGER_INLINE float Sign(float fInput) { return static_cast<float>(__fsel(fInput,0.5f,-0.5f)+__fsel(-fInput,-0.5f,0.5f)); }
	BURGER_INLINE double Sign(double dInput) { return __fsel(dInput,0.5f,-0.5f)+__fsel(-dInput,-0.5f,0.5f); }
#else
	BURGER_INLINE float Sign(float fInput) { return ((fInput > 0.0f) ? 1.0f : ((fInput < 0.0f) ? -1.0f : 0.0f)); }
	BURGER_INLINE double Sign(double dInput) { return ((dInput > 0.0) ? 1.0 : ((dInput < 0.0) ? -1.0 : 0.0)); }
#endif
#if defined(BURGER_METROWERKS) && defined(BURGER_POWERPC)
	BURGER_INLINE float Min(float fA,float fB) { return static_cast<float>(__fsel((fA-fB),fB,fA)); }
	BURGER_INLINE double Min(double dA,double dB) { return __fsel((dA-dB),dB,dA); }
	BURGER_INLINE float Max(float fA,float fB) { return static_cast<float>(__fsel((fA-fB),fA,fB)); }
	BURGER_INLINE double Max(double dA,double dB) { return __fsel((dA-dB),dA,dB); }
#elif defined(BURGER_MACOSX) && defined(BURGER_POWERPC)
	BURGER_INLINE float Min(float fA,float fB) { float fC=fA-fB; __asm__("fsel %0,%1,%2,%3":"=f" (fA) : "f" (fC),"f"(fB),"f"(fA)); return fA; }
	BURGER_INLINE double Min(double dA,double dB) { double dC=dA-dB; __asm__("fsel %0,%1,%2,%3":"=f" (dA) : "f" (dC),"f"(dB),"f"(dA)); return dA; }
	BURGER_INLINE float Max(float fA,float fB) { float fC=fA-fB; __asm__("fsel %0,%1,%2,%3":"=f" (fA) : "f" (fC),"f"(fA),"f"(fB)); return fA; }
	BURGER_INLINE double Max(double dA,double dB) { double dC=dA-dB; __asm__("fsel %0,%1,%2,%3":"=f" (dA) : "f" (dC),"f"(dA),"f"(dB)); return dA; }
#elif defined(BURGER_MSVC) && defined(BURGER_AMD64)
	BURGER_INLINE float Min(float fA,float fB) { return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(fA),_mm_set_ss(fB))); }
	BURGER_INLINE double Min(double dA,double dB) { return _mm_cvtsd_f64(_mm_min_sd(_mm_set_sd(dA),_mm_set_sd(dB))); }
	BURGER_INLINE float Max(float fA,float fB) { return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(fA),_mm_set_ss(fB))); }
	BURGER_INLINE double Max(double dA,double dB) { return _mm_cvtsd_f64(_mm_max_sd(_mm_set_sd(dA),_mm_set_sd(dB))); }
#else
	BURGER_INLINE float Min(float fA,float fB) { return ((fA < fB) ? fA : fB); }
	BURGER_INLINE double Min(double dA,double dB) { return ((dA < dB) ? dA : dB); }
	BURGER_INLINE float Max(float fA,float fB) { return ((fA > fB) ? fA : fB); }
	BURGER_INLINE double Max(double dA,double dB) { return ((dA > dB) ? dA : dB); }
#endif
	BURGER_INLINE float Clamp(float fIn,float fMin,float fMax) { fIn = Max(fIn,fMin); return Min(fIn,fMax); }
	BURGER_INLINE double Clamp(double dIn,double dMin,double dMax) { dIn = Max(dIn,dMin); return Min(dIn,dMax); }
	extern Word BURGER_API IsNan(float fInput);
	extern Word BURGER_API IsNan(double dInput);
	extern Word BURGER_API IsInf(float fInput);
	extern Word BURGER_API IsInf(double dInput);
	extern Word BURGER_API IsFinite(float fInput);
	extern Word BURGER_API IsFinite(double dInput);
	extern Word BURGER_API IsNormal(float fInput);
	extern Word BURGER_API IsNormal(double dInput);
	extern Word BURGER_API SignBit(float fInput);
	extern Word BURGER_API SignBit(double dInput);
	extern float BURGER_API Floor(float fInput);
	extern double BURGER_API Floor(double dInput);
	extern float BURGER_API Ceil(float fInput);
	extern double BURGER_API Ceil(double dInput);
	extern float BURGER_API Round(float fInput);
	extern double BURGER_API Round(double dInput);
	extern float BURGER_API RoundToZero(float fInput);
	extern double BURGER_API RoundToZero(double dInput);
	extern float BURGER_API ModuloRadians(float fInput);
	extern double BURGER_API ModuloRadians(double dInput);
	extern float BURGER_API Sin(float fInput);
	extern double BURGER_API Sin(double dInput);
	extern float BURGER_API Cos(float fInput);
	extern double BURGER_API Cos(double dInput);
	extern float BURGER_API Tan(float fInput);
	extern double BURGER_API Tan(double dInput);
	extern float BURGER_API ASin(float fInput);
	extern double BURGER_API ASin(double dInput);
	extern float BURGER_API ACos(float fInput);
	extern double BURGER_API ACos(double dInput);
	extern float BURGER_API ATan(float fInput);
	extern double BURGER_API ATan(double dInput);
	extern float BURGER_API ATan2(float fSin,float fCos);
	extern double BURGER_API ATan2(double dSin,double dCos);
	extern float BURGER_API Exp(float fInput);
	extern double BURGER_API Exp(double dInput);
	extern float BURGER_API Log(float fInput);
	extern double BURGER_API Log(double dInput);
	extern float BURGER_API Log2(float fInput);
	extern double BURGER_API Log2(double dInput);
	extern float BURGER_API Log10(float fInput);
	extern double BURGER_API Log10(double dInput);
	extern float BURGER_API Modf(float fInput,float *pInteger);
	extern double BURGER_API Modf(double dInput,double *pInteger);
	extern float BURGER_API Fmod(float fInput,float fDivisor);
	extern double BURGER_API Fmod(double dInput,double dDivisor);
}
namespace Burger {
struct FixedVector2D_t;
struct Vector2D_t {
	float x;			///< 32 bit floating point X value for the 2D Vector
	float y;			///< 32 bit floating point Y value for the 2D Vector
	BURGER_INLINE void Zero(void) { x = 0.0f; y = 0.0f; }
	BURGER_INLINE void One(void) { x = 1.0f; y = 1.0f; }
	BURGER_INLINE float GetX(void) const { return x; }
	BURGER_INLINE float GetY(void) const { return y; }
	BURGER_INLINE void SetX(float fX) { x=fX; }
	BURGER_INLINE void SetY(float fY) { y=fY; }
	BURGER_INLINE void Set(float fInput) { x = fInput; y = fInput; };
	BURGER_INLINE void Set(float fX,float fY) { x = fX; y = fY; };
	BURGER_INLINE void Set(const Vector2D_t *pInput) { *this = *pInput; }
	void BURGER_API Set(const FixedVector2D_t *pInput);
	BURGER_INLINE void Negate(void) { x = -x; y = -y; }
	BURGER_INLINE void Negate(float fX,float fY) { x = -fX; y = -fY; }
	BURGER_INLINE void Negate(const Vector2D_t *pInput) { x = -pInput->x; y = -pInput->y; }
	void BURGER_API Interpolate(const Vector2D_t *pFrom,const Vector2D_t *pTo,float fFactor);
	BURGER_INLINE float Dot(float fX,float fY) const { return (x*fX) + (y*fY); }
	BURGER_INLINE float Dot(const Vector2D_t *pInput) const { return (x*pInput->x) + (y*pInput->y); }
	BURGER_INLINE void Add(const Vector2D_t *pInput) { x += pInput->x; y += pInput->y; }
	BURGER_INLINE void Add(float fInput) { x += fInput; y += fInput; }
	BURGER_INLINE void Add(const Vector2D_t *pInput1,const Vector2D_t *pInput2) { x = pInput1->x+pInput2->x; y = pInput1->y+pInput2->y; }
	BURGER_INLINE void Add(const Vector2D_t *pInput,float fInput) { x = pInput->x+fInput; y = pInput->y+fInput; }
	BURGER_INLINE void Sub(const Vector2D_t *pInput) { x -= pInput->x; y -= pInput->y; }
	BURGER_INLINE void Sub(float fInput) { x -= fInput; y -= fInput; }
	BURGER_INLINE void Sub(const Vector2D_t *pInput1,const Vector2D_t *pInput2) { x = pInput1->x-pInput2->x; y = pInput1->y-pInput2->y; }
	BURGER_INLINE void Sub(const Vector2D_t *pInput,float fInput) { x = pInput->x-fInput; y = pInput->y-fInput; }
	BURGER_INLINE void Mul(const Vector2D_t *pInput) { x *= pInput->x; y *= pInput->y; }
	BURGER_INLINE void Mul(float fInput) { x *= fInput; y *= fInput; }
	BURGER_INLINE void Mul(const Vector2D_t *pInput1,const Vector2D_t *pInput2) { x = pInput1->x*pInput2->x; y = pInput1->y*pInput2->y; }
	BURGER_INLINE void Mul(const Vector2D_t *pInput,float fInput) { x = pInput->x*fInput; y = pInput->y*fInput; }
	BURGER_INLINE float Cross(float fX,float fY) const { return (x*fY) - (y*fX); }
	BURGER_INLINE float Cross(const Vector2D_t *pInput) const { return (x*pInput->y) - (y*pInput->x); }
	BURGER_INLINE float GetLengthSquared(void) const { return (x*x) + (y*y); }
	BURGER_INLINE float GetLength(void) const { return Sqrt((x*x) + (y*y)); }
	BURGER_INLINE float GetLengthFast(void) const { return Sqrt((x*x) + (y*y)); }
	void BURGER_API SetLength(float fInput);
	void BURGER_API SetLengthFast(float fInput);
	float BURGER_API GetDistanceSquared(float fX,float fY) const;
	float BURGER_API GetDistanceSquared(const Vector2D_t *pInput) const;
	float BURGER_API GetDistance(float fX,float fY) const;
	float BURGER_API GetDistance(const Vector2D_t *pInput) const;
	float BURGER_API GetDistanceFast(float fX,float fY) const;
	float BURGER_API GetDistanceFast(const Vector2D_t *pInput) const;
	void BURGER_API Normalize(void);
	void BURGER_API Normalize(float fX,float fY);
	void BURGER_API Normalize(const Vector2D_t *pInput);
	void BURGER_API NormalizeFast(void);
	void BURGER_API NormalizeFast(float fX,float fY);
	void BURGER_API NormalizeFast(const Vector2D_t *pInput);
	Word BURGER_API BitwiseEqual(const Vector2D_t *pInput) const;
	BURGER_INLINE float Determinant(const Vector2D_t* pInput1,const Vector2D_t *pInput2) const { return ((pInput1->x-x)*(pInput2->y-y))-((pInput1->y-y)*(pInput2->x-x)); }
	Word BURGER_API IsPointInTriangle(const Vector2D_t *pVertex1,const Vector2D_t *pVertex2,const Vector2D_t *pVertex3) const;
	BURGER_INLINE float & operator[](Word uInput) { return (&x)[uInput]; }
	BURGER_INLINE const float & operator[](Word uInput) const { return (&x)[uInput]; }
	BURGER_INLINE Word operator == (const Vector2D_t& rInput) const { return (x == rInput.x) && (y == rInput.y); }
	BURGER_INLINE Word operator != (const Vector2D_t& rInput) const { return (x != rInput.x) || (y != rInput.y); }
	BURGER_INLINE operator const float *() const { return &x; }
};
struct Word32ToVector2D_t {
	union {
		Word32 x[2];		///< Value as two 32 bit unsigned integers
		Vector2D_t v;		///< Value as two 32 bit floats
	};
	BURGER_INLINE operator const Vector2D_t &() const { return v; }
};
extern const Vector2D_t g_Vector2DZero;
extern const Vector2D_t g_Vector2DOne;
extern const Vector2D_t g_Vector2DOneX;
extern const Vector2D_t g_Vector2DOneY;
extern const Word32ToVector2D_t g_Vector2DMax;
extern const Word32ToVector2D_t g_Vector2DInfinity;
}
namespace Burger {
struct FixedVector3D_t;
struct Vector3D_t {
	float x;			///< 32 bit floating point X value for the 3D Vector
	float y;			///< 32 bit floating point Y value for the 3D Vector
	float z;			///< 32 bit floating point Z value for the 3D Vector
	BURGER_INLINE void Zero(void) { x = 0.0f; y = 0.0f; z = 0.0f; }
	BURGER_INLINE void One(void) { x = 1.0f; y = 1.0f; z = 1.0f; }
	BURGER_INLINE float GetX(void) const { return x; }
	BURGER_INLINE float GetY(void) const { return y; }
	BURGER_INLINE float GetZ(void) const { return z; }
	BURGER_INLINE void SetX(float fX) { x=fX; }
	BURGER_INLINE void SetY(float fY) { y=fY; }
	BURGER_INLINE void SetZ(float fZ) { z=fZ; }
	BURGER_INLINE void Set(float fInput) { x = fInput; y = fInput; z = fInput; };
	BURGER_INLINE void Set(float fX,float fY) { x = fX; y = fY; z = 0.0f; };
	BURGER_INLINE void Set(float fX,float fY,float fZ) { x = fX; y = fY; z = fZ; };
	BURGER_INLINE void Set(const Vector3D_t *pInput) { *this = *pInput; }
	void BURGER_API Set(const FixedVector3D_t *pInput);
	BURGER_INLINE void Negate(void) { x = -x; y = -y; z = -z; }
	BURGER_INLINE void Negate(float fX,float fY,float fZ) { x = -fX; y = -fY; z = -fZ; }
	BURGER_INLINE void Negate(const Vector3D_t *pInput) { x = -pInput->x; y = -pInput->y; z = -pInput->z; }
	void BURGER_API Interpolate(const Vector3D_t *pFrom,const Vector3D_t *pTo,float fFactor);
	BURGER_INLINE float Dot(float fX,float fY,float fZ) const { return (x*fX) + (y*fY) + (z*fZ); }
	BURGER_INLINE float Dot(const Vector3D_t *pInput) const { return (x*pInput->x) + (y*pInput->y) + (z*pInput->z); }
	BURGER_INLINE void Add(const Vector3D_t *pInput) { x += pInput->x; y += pInput->y; z += pInput->z; }
	BURGER_INLINE void Add(float fInput) { x += fInput; y += fInput; z += fInput; }
	BURGER_INLINE void Add(const Vector3D_t *pInput1,const Vector3D_t *pInput2) { x = pInput1->x+pInput2->x; y = pInput1->y+pInput2->y; z = pInput1->z+pInput2->z; }
	BURGER_INLINE void Add(const Vector3D_t *pInput,float fInput) { x = pInput->x+fInput; y = pInput->y+fInput; z = pInput->z+fInput; }
	BURGER_INLINE void Sub(const Vector3D_t *pInput) { x -= pInput->x; y -= pInput->y; z -= pInput->z; }
	BURGER_INLINE void Sub(float fInput) { x -= fInput; y -= fInput; z -= fInput; }
	BURGER_INLINE void Sub(const Vector3D_t *pInput1,const Vector3D_t *pInput2) { x = pInput1->x-pInput2->x; y = pInput1->y-pInput2->y; z = pInput1->z-pInput2->z; }
	BURGER_INLINE void Sub(const Vector3D_t *pInput,float fInput) { x = pInput->x-fInput; y = pInput->y-fInput; z = pInput->z-fInput; }
	BURGER_INLINE void Mul(const Vector3D_t *pInput) { x *= pInput->x; y *= pInput->y; z *= pInput->z; }
	BURGER_INLINE void Mul(float fInput) { x *= fInput; y *= fInput; z *= fInput; }
	BURGER_INLINE void Mul(const Vector3D_t *pInput1,const Vector3D_t *pInput2) { x = pInput1->x*pInput2->x; y = pInput1->y*pInput2->y; z = pInput1->z*pInput2->z; }
	BURGER_INLINE void Mul(const Vector3D_t *pInput,float fInput) { x = pInput->x*fInput; y = pInput->y*fInput; z = pInput->z*fInput; }
	BURGER_INLINE void MulAdd(const Vector3D_t *pMul,const Vector3D_t *pAdd) { x = (x*pMul->x)+pAdd->x; y = (y*pMul->y)+pAdd->y; z = (z*pMul->z)+pAdd->z; }
	BURGER_INLINE void MulAdd(const Vector3D_t *pMul1,const Vector3D_t *pMul2,const Vector3D_t *pAdd) { x = (pMul1->x*pMul2->x)+pAdd->x; y = (pMul1->y*pMul2->y)+pAdd->y; z = (pMul1->z*pMul2->z)+pAdd->z; }
	BURGER_INLINE void MulAdd(float fInput,const Vector3D_t *pAdd) { x = (x*fInput)+pAdd->x; y = (y*fInput)+pAdd->y; z = (z*fInput)+pAdd->z; }
	BURGER_INLINE void MulAdd(const Vector3D_t *pMul,float fInput,const Vector3D_t *pAdd) { x = (pMul->x*fInput)+pAdd->x; y = (pMul->y*fInput)+pAdd->y; z = (pMul->z*fInput)+pAdd->z; }
	void BURGER_API Cross(const Vector3D_t *pInput);
	void BURGER_API Cross(const Vector3D_t *pInput1,const Vector3D_t *pInput2);
	BURGER_INLINE float GetLengthSquared(void) const { return (x*x) + (y*y) + (z*z); }
	BURGER_INLINE float GetLength(void) const { return Sqrt((x*x) + (y*y) + (z*z)); }
	BURGER_INLINE float GetLengthFast(void) const { return Sqrt((x*x) + (y*y) + (z*z)); }
	void BURGER_API SetLength(float fInput);
	void BURGER_API SetLengthFast(float fInput);
	float BURGER_API GetDistanceSquared(float fX,float fY,float fZ) const;
	float BURGER_API GetDistanceSquared(const Vector3D_t *pInput) const;
	float BURGER_API GetDistance(float fX,float fY,float fZ) const;
	float BURGER_API GetDistance(const Vector3D_t *pInput) const;
	float BURGER_API GetDistanceFast(float fX,float fY,float fZ) const;
	float BURGER_API GetDistanceFast(const Vector3D_t *pInput) const;
	void BURGER_API Normalize(void);
	void BURGER_API Normalize(float fX,float fY,float fZ);
	void BURGER_API Normalize(const Vector3D_t *pInput);
	void BURGER_API PlaneNormal(const Vector3D_t *pOrigin,const Vector3D_t *pPoint1,const Vector3D_t *pPoint2);
	void BURGER_API NormalizeFast(void);
	void BURGER_API NormalizeFast(float fX,float fY,float fZ);
	void BURGER_API NormalizeFast(const Vector3D_t *pInput);
	Word BURGER_API Equal(const Vector3D_t *pInput) const;
	Word BURGER_API Equal(const Vector3D_t *pInput,float fRange) const;
	Word BURGER_API BitwiseEqual(const Vector3D_t *pInput) const;
	BURGER_INLINE float & operator[](Word uInput) { return (&x)[uInput]; }
	BURGER_INLINE const float & operator[](Word uInput) const { return (&x)[uInput]; }
	BURGER_INLINE Word operator == (const Vector3D_t& rInput) const { return (x == rInput.x) && (y == rInput.y) && (z == rInput.z); }
	BURGER_INLINE Word operator != (const Vector3D_t& rInput) const { return (x != rInput.x) || (y != rInput.y) || (z != rInput.z); }
	BURGER_INLINE operator const float *() const { return &x; }
};
struct Word32ToVector3D_t {
	union {
		Word32 x[3];		///< Value as three 32 bit unsigned integers
		Vector3D_t v;		///< Value as three 32 bit floats
	};
	BURGER_INLINE operator const Vector3D_t &() const { return v; }
};
extern const Vector3D_t g_Vector3DZero;
extern const Vector3D_t g_Vector3DOne;
extern const Vector3D_t g_Vector3DOneX;
extern const Vector3D_t g_Vector3DOneY;
extern const Vector3D_t g_Vector3DOneZ;
extern const Word32ToVector3D_t g_Vector3DMax;
extern const Word32ToVector3D_t g_Vector3DInfinity;
}
namespace Burger {
struct FixedVector4D_t;
struct Vector4D_t {
	float x;			///< 32 bit floating point X value for the 4D Vector (LeftX)
	float y;			///< 32 bit floating point Y value for the 4D Vector (TopY)
	float z;			///< 32 bit floating point Z value for the 4D Vector (RightX)
	float w;			///< 32 bit floating point W value for the 4D Vector (BottomY)
	BURGER_INLINE void Zero(void) { x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; }
	BURGER_INLINE void One(void) { x = 1.0f; y = 1.0f; z = 1.0f; w = 1.0f; }
	BURGER_INLINE void Identity(void) { x = 0.0f; y = 0.0f; z = 0.0f; w = 1.0f; }
	BURGER_INLINE float GetX(void) const { return x; }
	BURGER_INLINE float GetY(void) const { return y; }
	BURGER_INLINE float GetZ(void) const { return z; }
	BURGER_INLINE float GetW(void) const { return w; }
	BURGER_INLINE void SetX(float fX) { x=fX; }
	BURGER_INLINE void SetY(float fY) { y=fY; }
	BURGER_INLINE void SetZ(float fZ) { z=fZ; }
	BURGER_INLINE void SetW(float fW) { z=fW; }
	BURGER_INLINE void Set(float fInput) { x = fInput; y = fInput; z = fInput; w = fInput; };
	BURGER_INLINE void Set(float fX,float fY) { x = fX; y = fY; z = 0.0f; w = 1.0f; };
	BURGER_INLINE void Set(float fX,float fY,float fZ) { x = fX; y = fY; z = fZ; w = 1.0f; };
	BURGER_INLINE void Set(float fX,float fY,float fZ,float fW) { x = fX; y = fY; z = fZ; w = fW; };
	BURGER_INLINE void Set(const Vector4D_t *pInput) { *this = *pInput; }
	void BURGER_API Set(const FixedVector4D_t *pInput);
	BURGER_INLINE void SetRect(float fX,float fY) { x = fX; y = fY; z = fX; w = fY; };
	BURGER_INLINE void SetRect(const Vector2D_t *pMinMax) { x = pMinMax->x; y = pMinMax->y; z = pMinMax->x; w = pMinMax->y; }
	BURGER_INLINE void SetRect(const Vector2D_t *pMin,const Vector2D_t *pMax) { x = pMin->x; y = pMin->y; z = pMax->x; w = pMax->y; }
	BURGER_INLINE void Negate(void) { x = -x; y = -y; z = -z; w = -w; }
	BURGER_INLINE void Negate(float fX,float fY,float fZ,float fW) { x = -fX; y = -fY; z = -fZ; w = -fW; }
	BURGER_INLINE void Negate(const Vector4D_t *pInput) { x = -pInput->x; y = -pInput->y; z = -pInput->z; w = -pInput->w; }
	void BURGER_API Interpolate(const Vector4D_t *pFrom,const Vector4D_t *pTo,float fFactor);
	BURGER_INLINE float Dot(float fX,float fY,float fZ,float fW) const { return (x*fX) + (y*fY) + (z*fZ) + (w*fW); }
	BURGER_INLINE float Dot(const Vector4D_t *pInput) const { return (x*pInput->x) + (y*pInput->y) + (z*pInput->z) + (w*pInput->w); }
	BURGER_INLINE void Add(const Vector4D_t *pInput) { x += pInput->x; y += pInput->y; z += pInput->z; w += pInput->w; }
	BURGER_INLINE void Add(float fInput) { x += fInput; y += fInput; z += fInput; w += fInput; }
	BURGER_INLINE void Add(const Vector4D_t *pInput1,const Vector4D_t *pInput2) { x = pInput1->x+pInput2->x; y = pInput1->y+pInput2->y; z = pInput1->z+pInput2->z; w = pInput1->w+pInput2->w; }
	BURGER_INLINE void Add(const Vector4D_t *pInput,float fInput) { x = pInput->x+fInput; y = pInput->y+fInput; z = pInput->z+fInput; w = pInput->w+fInput; }
	BURGER_INLINE void Sub(const Vector4D_t *pInput) { x -= pInput->x; y -= pInput->y; z -= pInput->z; w -= pInput->w; }
	BURGER_INLINE void Sub(float fInput) { x -= fInput; y -= fInput; z -= fInput; w -= fInput; }
	BURGER_INLINE void Sub(const Vector4D_t *pInput1,const Vector4D_t *pInput2) { x = pInput1->x-pInput2->x; y = pInput1->y-pInput2->y; z = pInput1->z-pInput2->z; w = pInput1->w-pInput2->w; }
	BURGER_INLINE void Sub(const Vector4D_t *pInput,float fInput) { x = pInput->x-fInput; y = pInput->y-fInput; z = pInput->z-fInput; w = pInput->w-fInput; }
	BURGER_INLINE void Mul(const Vector4D_t *pInput) { x *= pInput->x; y *= pInput->y; z *= pInput->z; w *= pInput->w; }
	BURGER_INLINE void Mul(float fInput) { x *= fInput; y *= fInput; z *= fInput; w *= fInput; }
	BURGER_INLINE void Mul(const Vector4D_t *pInput1,const Vector4D_t *pInput2) { x = pInput1->x*pInput2->x; y = pInput1->y*pInput2->y; z = pInput1->z*pInput2->z; w = pInput1->w*pInput2->w; }
	BURGER_INLINE void Mul(const Vector4D_t *pInput,float fInput) { x = pInput->x*fInput; y = pInput->y*fInput; z = pInput->z*fInput; w = pInput->w*fInput; }
	BURGER_INLINE float GetLengthSquared(void) const { return (x*x) + (y*y) + (z*z) + (w*w); }
	BURGER_INLINE float GetLength(void) const { return Sqrt((x*x) + (y*y) + (z*z) + (w*w)); }
	BURGER_INLINE float GetLengthFast(void) const { return Sqrt((x*x) + (y*y) + (z*z) + (w*w)); }
	void BURGER_API SetLength(float fInput);
	void BURGER_API SetLengthFast(float fInput);
	float BURGER_API GetDistanceSquared(float fX,float fY,float fZ,float fW) const;
	float BURGER_API GetDistanceSquared(const Vector4D_t *pInput) const;
	float BURGER_API GetDistance(float fX,float fY,float fZ,float fW) const;
	float BURGER_API GetDistance(const Vector4D_t *pInput) const;
	float BURGER_API GetDistanceFast(float fX,float fY,float fZ,float fW) const;
	float BURGER_API GetDistanceFast(const Vector4D_t *pInput) const;
	void BURGER_API Normalize(void);
	void BURGER_API Normalize(float fX,float fY,float fZ,float fW);
	void BURGER_API Normalize(const Vector4D_t *pInput);
	void BURGER_API NormalizeFast(void);
	void BURGER_API NormalizeFast(float fX,float fY,float fZ,float fW);
	void BURGER_API NormalizeFast(const Vector4D_t *pInput);
	BURGER_INLINE float Dot3(float fX,float fY,float fZ) const { return (x*fX) + (y*fY) + (z*fZ); }
	BURGER_INLINE float Dot3(const Vector4D_t *pInput) const { return (x*pInput->x) + (y*pInput->y) + (z*pInput->z); }
	BURGER_INLINE void QuaternionNegate(void) { x = -x; y = -y; z = -z; }
	BURGER_INLINE void QuaternionNegate(float fX,float fY,float fZ,float fW) { x = -fX; y = -fY; z = -fZ; w = fW; }
	BURGER_INLINE void QuaternionNegate(const Vector4D_t *pInput) { x = -pInput->x; y = -pInput->y; z = -pInput->z; w = pInput->w; }
	void BURGER_API QuaternionMul(const Vector4D_t *pInput);
	void BURGER_API QuaternionMul(const Vector4D_t *pInput1,const Vector4D_t *pInput2);
	void BURGER_API QuaternionMulNormalize(const Vector4D_t *pInput);
	void BURGER_API QuaternionMulNormalize(const Vector4D_t *pInput1,const Vector4D_t *pInput2);
	Word BURGER_API BitwiseEqual(const Vector4D_t *pInput) const;
	BURGER_INLINE float & operator[](Word uInput) { return (&x)[uInput]; }
	BURGER_INLINE const float & operator[](Word uInput) const { return (&x)[uInput]; }
	BURGER_INLINE Word operator == (const Vector4D_t& rInput) const { return (x == rInput.x) && (y == rInput.y) && (z == rInput.z) && (w == rInput.z); }
	BURGER_INLINE Word operator != (const Vector4D_t& rInput) const { return (x != rInput.x) || (y != rInput.y) || (z != rInput.z) || (w != rInput.z); }
	BURGER_INLINE operator const float *() const { return &x; }
	BURGER_INLINE const Vector2D_t *GetTopLeft(void) const { return reinterpret_cast<const Vector2D_t *>(&x); }
	BURGER_INLINE const Vector2D_t *GetBottomRight(void) const { return reinterpret_cast<const Vector2D_t *>(&z); }
	BURGER_INLINE Vector2D_t *GetTopLeft(void) { return reinterpret_cast<Vector2D_t *>(&x); }
	BURGER_INLINE Vector2D_t *GetBottomRight(void) { return reinterpret_cast<Vector2D_t *>(&z); }
	BURGER_INLINE float GetWidth(void) const { return z - x; }
	BURGER_INLINE float GetHeight(void) const { return w - y; }
	BURGER_INLINE float GetLeft(void) const { return x; }
	BURGER_INLINE float GetTop(void) const { return y; }
	BURGER_INLINE float GetRight(void) const { return z; }
	BURGER_INLINE float GetBottom(void) const { return w; }
	BURGER_INLINE void SetWidth(float fWidth) { z = x+fWidth; }
	BURGER_INLINE void SetHeight(float fHeight) { w = y+fHeight; }
	BURGER_INLINE void SetSize(float fWidth,float fHeight) { z = x+fWidth; w = y+fHeight; }
	BURGER_INLINE void SetLeft(float fLeft) { x = fLeft; }
	BURGER_INLINE void SetTop(float fTop) { y = fTop; }
	BURGER_INLINE void SetRight(float fRight) { z = fRight; }
	BURGER_INLINE void SetBottom(float fBottom) { w = fBottom; }
	BURGER_INLINE Word IsInsideRect(float fX,float fY) const { return ((fX >= x) && (fX <= z) && (fY >= y) && (fY <= w)); }
	BURGER_INLINE Word IsInsideRect(const Vector2D_t *pInput) const { return ((pInput->x >= x) && (pInput->x <= z) && (pInput->y >= y) && (pInput->y <= w)); }
	void BURGER_API ExpandRect(float fX, float fY);
	void BURGER_API ExpandRect(const Vector2D_t *pInput);
	void BURGER_API ExpandRect(const Vector4D_t *pInput);
};
extern const Vector4D_t g_Vector4DZero;
extern const Vector4D_t g_Vector4DOne;
extern const Vector4D_t g_Vector4DOneX;
extern const Vector4D_t g_Vector4DOneY;
extern const Vector4D_t g_Vector4DOneZ;
extern const Vector4D_t g_Vector4DOneW;
}
namespace Burger {
struct FixedVector2D_t {
	Fixed32 x;			///< 32 bit fixed point X value for the 2D Vector
	Fixed32 y;			///< 32 bit fixed point Y value for the 2D Vector
	BURGER_INLINE void Zero(void) { x=0; y=0; }
	BURGER_INLINE void One(void) { x = 65536; y = 65536; }
	BURGER_INLINE Fixed32 GetX(void) const { return x; }
	BURGER_INLINE Fixed32 GetY(void) const { return y; }
	BURGER_INLINE void SetX(Fixed32 fX) { x=fX; }
	BURGER_INLINE void SetY(Fixed32 fY) { y=fY; }
	BURGER_INLINE void Set(Fixed32 fX,Fixed32 fY) { x=fX; y=fY; }
	BURGER_INLINE void Negate(void) { x = -x; y = -y; }
	BURGER_INLINE void Negate(Fixed32 fX,Fixed32 fY) { x = -fX; y = -fY; }
	BURGER_INLINE void Negate(const FixedVector2D_t *pInput) { x = -pInput->x; y = -pInput->y; }
};
}
namespace Burger {
struct FixedVector3D_t {
	Fixed32 x;			///< X value for the 3D Vector
	Fixed32 y;			///< Y value for the 3D Vector
	Fixed32 z;			///< Z value for the 3D Vector
	BURGER_INLINE void Zero(void) { x=0; y=0; z=0; }
	BURGER_INLINE void One(void) { x = 65536; y = 65536; z = 65536; }
	BURGER_INLINE Fixed32 GetX(void) const { return x; }
	BURGER_INLINE Fixed32 GetY(void) const { return y; }
	BURGER_INLINE Fixed32 GetZ(void) const { return z; }
	BURGER_INLINE void SetX(Fixed32 fX) { x=fX; }
	BURGER_INLINE void SetY(Fixed32 fY) { y=fY; }
	BURGER_INLINE void SetZ(Fixed32 fZ) { z=fZ; }
	BURGER_INLINE void Set(Fixed32 fX,Fixed32 fY,Fixed32 fZ) { x=fX; y=fY; z=fZ; }
	BURGER_INLINE void Set(const FixedVector3D_t *pInput) { *this = *pInput; }
	void BURGER_API Set(const Vector3D_t *pInput);
	void BURGER_API SetAsInt(const Vector3D_t *pInput);
	void BURGER_API Negate(void);
	void BURGER_API Negate(const FixedVector3D_t *pInput);
	void BURGER_API Add(const FixedVector3D_t *pInput);
	void BURGER_API Add(const FixedVector3D_t *pInput1,const FixedVector3D_t *pInput2);
	void BURGER_API Sub(const FixedVector3D_t *pInput);
	void BURGER_API Sub(const FixedVector3D_t *pInput1,const FixedVector3D_t *pInput2);
	Fixed32 BURGER_API Dot(const FixedVector3D_t *pInput) const;
	void BURGER_API Cross(const FixedVector3D_t *pInput1,const FixedVector3D_t *pInput2);
};
extern const FixedVector3D_t s_FixedVector3DZero;
extern const FixedVector3D_t s_FixedVector3DOne;
extern const FixedVector3D_t s_FixedVector3DOneX;
extern const FixedVector3D_t s_FixedVector3DOneY;
extern const FixedVector3D_t s_FixedVector3DOneZ;
}
namespace Burger {
struct FixedVector4D_t {
	Fixed32 x;			///< 32 bit fixed point X value for the 4D Vector
	Fixed32 y;			///< 32 bit fixed point Y value for the 4D Vector
	Fixed32 z;			///< 32 bit fixed point Z value for the 4D Vector
	Fixed32 w;			///< 32 bit fixed point W value for the 4D Vector
	BURGER_INLINE void Zero(void) { x = 0; y = 0; z = 0; w = 0; }
	BURGER_INLINE void One(void) { x = 65536; y = 65536; z = 65536; w = 65536; }
	BURGER_INLINE void Identity(void) { x = 0; y = 0; z = 0; w = FLOATTOFIXED(1.0f); }
	BURGER_INLINE Fixed32 GetX(void) const { return x; }
	BURGER_INLINE Fixed32 GetY(void) const { return y; }
	BURGER_INLINE Fixed32 GetZ(void) const { return z; }
	BURGER_INLINE Fixed32 GetW(void) const { return w; }
	BURGER_INLINE void SetX(Fixed32 fX) { x=fX; }
	BURGER_INLINE void SetY(Fixed32 fY) { y=fY; }
	BURGER_INLINE void SetZ(Fixed32 fZ) { z=fZ; }
	BURGER_INLINE void SetW(Fixed32 fW) { z=fW; }
	BURGER_INLINE void Set(Fixed32 fX,Fixed32 fY,Fixed32 fZ) { x = fX; y = fY; z = fZ; w = FLOATTOFIXED(1.0f); };
	BURGER_INLINE void Set(Fixed32 fX,Fixed32 fY,Fixed32 fZ,Fixed32 fW) { x=fX; y=fY; z=fZ; w=fW; }
	BURGER_INLINE void Set(const FixedVector4D_t *pInput) { *this = *pInput; }
	BURGER_INLINE void Negate(void) { x = -x; y = -y; z = -z; w = -w; }
	BURGER_INLINE void Negate(Fixed32 fX,Fixed32 fY,Fixed32 fZ,Fixed32 fW) { x = -fX; y = -fY; z = -fZ; w = -fW; }
	BURGER_INLINE void Negate(const FixedVector4D_t *pInput) { x = -pInput->x; y = -pInput->y; z = -pInput->z; w = -pInput->w; }
};
extern const FixedVector4D_t s_FixedVector4DZero;
extern const FixedVector4D_t s_FixedVector4DOne;
extern const FixedVector4D_t s_FixedVector4DOneX;
extern const FixedVector4D_t s_FixedVector4DOneY;
extern const FixedVector4D_t s_FixedVector4DOneZ;
extern const FixedVector4D_t s_FixedVector4DOneW;
}
namespace Burger {
struct FixedMatrix3D_t;
struct Matrix4D_t;
struct Matrix3D_t {
	Vector3D_t x;	///< 32 bit floating point X row for the 3D Matrix
	Vector3D_t y;	///< 32 bit floating point Y row for the 3D Matrix
	Vector3D_t z;	///< 32 bit floating point Z row for the 3D Matrix
	void BURGER_API Zero(void);
	void BURGER_API Identity(void);
	void BURGER_API Set(const Matrix3D_t *pInput);
	void BURGER_API Set(const FixedMatrix3D_t *pInput);
	void BURGER_API Set(const Matrix4D_t *pInput);
	void BURGER_API SetYaw(float fYaw);
	void BURGER_API SetPitch(float fPitch);
	void BURGER_API SetRoll(float fRoll);
	void BURGER_API SetYXZ(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetYZX(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetXYZ(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetXZY(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetZYX(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetZXY(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetTranslate(float fX,float fY);
	void BURGER_API SetFromQuaternion(const Vector4D_t *pInput);
	void BURGER_API TransposeSetYaw(float fYaw);
	void BURGER_API TransposeSetPitch(float fPitch);
	void BURGER_API TransposeSetRoll(float fRoll);
	void BURGER_API TransposeSetYXZ(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetYZX(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetXYZ(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetXZY(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetZYX(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetZXY(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetFromQuaternion(const Vector4D_t *pInput);
	void BURGER_API SetScale(float fX,float fY,float fZ);
	void BURGER_API Transpose(void);
	void BURGER_API Transpose(const Matrix3D_t *pInput);
	void BURGER_API GetXRow(Vector3D_t *pOutput) const;
	void BURGER_API GetYRow(Vector3D_t *pOutput) const;
	void BURGER_API GetZRow(Vector3D_t *pOutput) const;
	void BURGER_API GetXColumn(Vector3D_t *pOutput) const;
	void BURGER_API GetYColumn(Vector3D_t *pOutput) const;
	void BURGER_API GetZColumn(Vector3D_t *pOutput) const;
	BURGER_INLINE void SetXRow(const Vector3D_t *pInput) { x.x = pInput->x; x.y = pInput->y; x.z = pInput->z; }
	BURGER_INLINE void SetXRow(float fX,float fY,float fZ) { x.x = fX; x.y = fY; x.z = fZ; }
	BURGER_INLINE void SetYRow(const Vector3D_t *pInput) { y.x = pInput->x; y.y = pInput->y; y.z = pInput->z; }
	BURGER_INLINE void SetYRow(float fX,float fY,float fZ) { y.x = fX; y.y = fY; y.z = fZ; }
	BURGER_INLINE void SetZRow(const Vector3D_t *pInput) { z.x = pInput->x; z.y = pInput->y; z.z = pInput->z; }
	BURGER_INLINE void SetZRow(float fX,float fY,float fZ) { z.x = fX; z.y = fY; z.z = fZ; }
	BURGER_INLINE void SetXColumn(const Vector3D_t *pInput) { x.x = pInput->x; y.x = pInput->y; z.x = pInput->z; }
	BURGER_INLINE void SetXColumn(float fX,float fY,float fZ) { x.x = fX; y.x = fY; z.x = fZ; }
	BURGER_INLINE void SetYColumn(const Vector3D_t *pInput) { x.y = pInput->x; y.y = pInput->y; z.y = pInput->z; }
	BURGER_INLINE void SetYColumn(float fX,float fY,float fZ) { x.y = fX; y.y = fY; z.y = fZ; }
	BURGER_INLINE void SetZColumn(const Vector3D_t *pInput) { x.z = pInput->x; y.z = pInput->y; z.z = pInput->z; }
	BURGER_INLINE void SetZColumn(float fX,float fY,float fZ) { x.z = fX; y.z = fY; z.z = fZ; }
	void BURGER_API Multiply(const Matrix3D_t *pInput);
	void BURGER_API Multiply(const Matrix3D_t *pInput1,const Matrix3D_t *pInput2);
	void BURGER_API Multiply(float fScale);
	void BURGER_API Multiply(const Matrix3D_t *pInput,float fScale);
	void BURGER_API Multiply(float fScaleX,float fScaleY,float fScaleZ);
	void BURGER_API Multiply(const Matrix3D_t *pInput,float fScaleX,float fScaleY,float fScaleZ);
	void BURGER_API TransposeMultiply(float fScaleX,float fScaleY,float fScaleZ);
	void BURGER_API TransposeMultiply(const Matrix3D_t *pInput,float fScaleX,float fScaleY,float fScaleZ);
	void BURGER_API Transform(Vector3D_t *pInput) const;
	void BURGER_API Transform(Vector3D_t *pOutput,const Vector3D_t *pInput) const;
	void BURGER_API TransformAdd(Vector3D_t *pInput,const Vector3D_t *pTranslate) const;
	void BURGER_API TransformAdd(Vector3D_t *pOutput,const Vector3D_t *pInput,const Vector3D_t *pTranslate) const;
	void BURGER_API TransposeTransform(Vector3D_t *pInput) const;
	void BURGER_API TransposeTransform(Vector3D_t *pOutput,const Vector3D_t *pInput) const;
	void BURGER_API TransposeTransformAdd(Vector3D_t *pInput,const Vector3D_t *pTranslate) const;
	void BURGER_API TransposeTransformAdd(Vector3D_t *pOutput,const Vector3D_t *pInput,const Vector3D_t *pTranslate) const;
	Word BURGER_API AffineInverse(const Matrix3D_t *pInput);
	void BURGER_API Yaw(float fYaw);
	void BURGER_API Pitch(float fPitch);
	void BURGER_API Roll(float fRoll);
	BURGER_INLINE operator const float *() const { return &x.x; }
};
extern const Matrix3D_t g_Matrix3DIdentity;
}
namespace Burger {
struct FixedMatrix4D_t;
struct Matrix4D_t {
	Vector4D_t x;	///< 32 bit floating point X row for the 4D Matrix
	Vector4D_t y;	///< 32 bit floating point Y row for the 4D Matrix
	Vector4D_t z;	///< 32 bit floating point Z row for the 4D Matrix
	Vector4D_t w;	///< 32 bit floating point W row for the 4D Matrix
	void BURGER_API Zero(void);
	void BURGER_API Identity(void);
	void BURGER_API Set(const Matrix4D_t *pInput);
	void BURGER_API Set(const FixedMatrix4D_t *pInput);
	void BURGER_API Set(const Matrix3D_t *pInput);
	void BURGER_API SetYaw(float fYaw);
	void BURGER_API SetPitch(float fPitch);
	void BURGER_API SetRoll(float fRoll);
	void BURGER_API SetYXZ(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetYZX(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetXYZ(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetXZY(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetZYX(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetZXY(float fYaw,float fPitch,float fRoll);
	void BURGER_API SetTranslate(float fX,float fY,float fZ);
	void BURGER_API SetFromQuaternion(const Vector4D_t *pInput);
	void BURGER_API TransposeSetYaw(float fYaw);
	void BURGER_API TransposeSetPitch(float fPitch);
	void BURGER_API TransposeSetRoll(float fRoll);
	void BURGER_API TransposeSetYXZ(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetYZX(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetXYZ(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetXZY(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetZYX(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetZXY(float fYaw,float fPitch,float fRoll);
	void BURGER_API TransposeSetFromQuaternion(const Vector4D_t *pInput);
	void BURGER_API SetScale(float fX,float fY,float fZ);
	void BURGER_API SetScale(float fX,float fY,float fZ,float fW);
	void BURGER_API SetFrustum(float fLeft,float fRight,float fBottom,float fTop,float fNear,float fFar);
	void BURGER_API TransposeSetFrustum(float fLeft,float fRight,float fBottom,float fTop,float fNear,float fFar);
	void BURGER_API SetOrtho(float fLeft,float fRight,float fBottom,float fTop,float fNear,float fFar);
	void BURGER_API TransposeSetOrtho(float fLeft,float fRight,float fBottom,float fTop,float fNear,float fFar);
	void BURGER_API SetPerspective(float fFieldOfViewY,float fAspect,float fNear,float fFar);
	void BURGER_API TransposeSetPerspective(float fFieldOfViewY,float fAspect,float fNear,float fFar);
	void BURGER_API Transpose(void);
	void BURGER_API Transpose(const Matrix4D_t *pInput);
	void BURGER_API GetXRow(Vector3D_t *pOutput) const;
	void BURGER_API GetXRow(Vector4D_t *pOutput) const;
	void BURGER_API GetYRow(Vector3D_t *pOutput) const;
	void BURGER_API GetYRow(Vector4D_t *pOutput) const;
	void BURGER_API GetZRow(Vector3D_t *pOutput) const;
	void BURGER_API GetZRow(Vector4D_t *pOutput) const;
	void BURGER_API GetWRow(Vector3D_t *pOutput) const;
	void BURGER_API GetWRow(Vector4D_t *pOutput) const;
	void BURGER_API GetXColumn(Vector3D_t *pOutput) const;
	void BURGER_API GetXColumn(Vector4D_t *pOutput) const;
	void BURGER_API GetYColumn(Vector3D_t *pOutput) const;
	void BURGER_API GetYColumn(Vector4D_t *pOutput) const;
	void BURGER_API GetZColumn(Vector3D_t *pOutput) const;
	void BURGER_API GetZColumn(Vector4D_t *pOutput) const;
	void BURGER_API GetWColumn(Vector3D_t *pOutput) const;
	void BURGER_API GetWColumn(Vector4D_t *pOutput) const;
	void BURGER_API SetXRow(const Vector3D_t *pInput);
	void BURGER_API SetXRow(const Vector4D_t *pInput);
	void BURGER_API SetYRow(const Vector3D_t *pInput);
	void BURGER_API SetYRow(const Vector4D_t *pInput);
	void BURGER_API SetZRow(const Vector3D_t *pInput);
	void BURGER_API SetZRow(const Vector4D_t *pInput);
	void BURGER_API SetWRow(const Vector3D_t *pInput);
	void BURGER_API SetWRow(const Vector4D_t *pInput);
	void BURGER_API SetXColumn(const Vector3D_t *pInput);
	void BURGER_API SetXColumn(const Vector4D_t *pInput);
	void BURGER_API SetYColumn(const Vector3D_t *pInput);
	void BURGER_API SetYColumn(const Vector4D_t *pInput);
	void BURGER_API SetZColumn(const Vector3D_t *pInput);
	void BURGER_API SetZColumn(const Vector4D_t *pInput);
	void BURGER_API SetWColumn(const Vector3D_t *pInput);
	void BURGER_API SetWColumn(const Vector4D_t *pInput);
	void BURGER_API Multiply(const Matrix4D_t *pInput);
	void BURGER_API Multiply(const Matrix4D_t *pInput1,const Matrix4D_t *pInput2);
	void BURGER_API Multiply(float fScale);
	void BURGER_API Multiply(const Matrix4D_t *pInput,float fScale);
	void BURGER_API Multiply(float fScaleX,float fScaleY,float fScaleZ);
	void BURGER_API Multiply(const Matrix4D_t *pInput,float fScaleX,float fScaleY,float fScaleZ);
	void BURGER_API Multiply(float fScaleX,float fScaleY,float fScaleZ,float fScaleW);
	void BURGER_API Multiply(const Matrix4D_t *pInput,float fScaleX,float fScaleY,float fScaleZ,float fScaleW);
	void BURGER_API Multiply3x3(float fInput);
	void BURGER_API Multiply3x3(const Matrix4D_t *pInput,float fInput);
	void BURGER_API TransposeMultiply(float fScaleX,float fScaleY,float fScaleZ);
	void BURGER_API TransposeMultiply(const Matrix4D_t *pInput,float fScaleX,float fScaleY,float fScaleZ);
	void BURGER_API TransposeMultiply(float fScaleX,float fScaleY,float fScaleZ,float fScaleW);
	void BURGER_API TransposeMultiply(const Matrix4D_t *pInput,float fScaleX,float fScaleY,float fScaleZ,float fScaleW);
	void BURGER_API Transform(Vector3D_t *pInput) const;
	void BURGER_API Transform(Vector4D_t *pInput) const;
	void BURGER_API Transform(Vector3D_t *pOutput,const Vector3D_t *pInput) const;
	void BURGER_API Transform(Vector4D_t *pOutput,const Vector4D_t *pInput) const;
	void BURGER_API TransposeTransform(Vector3D_t *pInput) const;
	void BURGER_API TransposeTransform(Vector4D_t *pInput) const;
	void BURGER_API TransposeTransform(Vector3D_t *pOutput,const Vector3D_t *pInput) const;
	void BURGER_API TransposeTransform(Vector4D_t *pOutput,const Vector4D_t *pInput) const;
	void BURGER_API Transform3x3(Vector3D_t *pInput) const;
	void BURGER_API Transform3x3(Vector3D_t *pOutput,const Vector3D_t *pInput) const;
	void BURGER_API TransposeTransform3x3(Vector3D_t *pInput) const;
	void BURGER_API TransposeTransform3x3(Vector3D_t *pOutput,const Vector3D_t *pInput) const;
	void BURGER_API Yaw(float fYaw);
	void BURGER_API Pitch(float fPitch);
	void BURGER_API Roll(float fRoll);
	void BURGER_API Rotate(float fRadians,float fX,float fY,float fZ);
	void BURGER_API Translate(float fX,float fY,float fZ);
	void BURGER_API TransposeTranslate(float fX,float fY,float fZ);
	Word BURGER_API AffineInverse(const Matrix4D_t *pInput);
	void BURGER_API PerspectiveFovLH(float fFieldOfViewY,float fAspect,float fNear,float fFar);
	void BURGER_API PerspectiveFovRH(float fFieldOfViewY,float fAspect,float fNear,float fFar);
	BURGER_INLINE operator const float *() const { return &x.x; }
};
extern const Matrix4D_t s_Matrix4DIdentity;
}
namespace Burger {
struct FixedMatrix3D_t {
	FixedVector3D_t x;	///< 32 bit fixed point X row for the 3D Matrix
	FixedVector3D_t y;	///< 32 bit fixed point Y row for the 3D Matrix
	FixedVector3D_t z;	///< 32 bit fixed point Z row for the 3D Matrix
	void BURGER_API Zero(void);
	void BURGER_API Identity(void);
	void BURGER_API Set(const Matrix3D_t *pInput);
	void BURGER_API Transpose(void);
	void BURGER_API Transpose(const FixedMatrix3D_t *pInput);
	void BURGER_API GetXRow(FixedVector3D_t *pOutput) const;
	void BURGER_API GetYRow(FixedVector3D_t *pOutput) const;
	void BURGER_API GetZRow(FixedVector3D_t *pOutput) const;
	void BURGER_API GetXColumn(FixedVector3D_t *pOutput) const;
	void BURGER_API GetYColumn(FixedVector3D_t *pOutput) const;
	void BURGER_API GetZColumn(FixedVector3D_t *pOutput) const;
	void BURGER_API SetXRow(const FixedVector3D_t *pInput);
	void BURGER_API SetYRow(const FixedVector3D_t *pInput);
	void BURGER_API SetZRow(const FixedVector3D_t *pInput);
	void BURGER_API SetXColumn(const FixedVector3D_t *pInput);
	void BURGER_API SetYColumn(const FixedVector3D_t *pInput);
	void BURGER_API SetZColumn(const FixedVector3D_t *pInput);
	void BURGER_API Multiply(Fixed32 fScale);
	void BURGER_API Multiply(const FixedMatrix3D_t *pInput,Fixed32 fScale);
};
extern const FixedMatrix3D_t s_FixedMatrix3DIdentity;
}
namespace Burger {
struct FixedMatrix4D_t {
	FixedVector4D_t x;	///< X row for the 4x4 Matrix
	FixedVector4D_t y;	///< Y row for the 4x4 Matrix
	FixedVector4D_t z;	///< Z row for the 4x4 Matrix
	FixedVector4D_t w;	///< W row for the 4x4 Matrix
	void BURGER_API Zero(void);
	void BURGER_API Identity(void);
	void BURGER_API Set(const Matrix4D_t *pInput);
	void BURGER_API Set(const FixedMatrix4D_t *pInput);
	void BURGER_API SetTranslate(Fixed32 fX,Fixed32 fY,Fixed32 fZ);
	void BURGER_API SetScale(Fixed32 fX,Fixed32 fY,Fixed32 fZ);
	void BURGER_API SetScale(Fixed32 fX,Fixed32 fY,Fixed32 fZ,Fixed32 fW);
};
extern const FixedMatrix4D_t s_FixedMatrix4DIdentity;
}
namespace Burger {
class DoublyLinkedList {
   	BURGER_DISABLECOPYCONSTRUCTORS(DoublyLinkedList);
	DoublyLinkedList *m_pNext;		///< Pointer to the next entry
	DoublyLinkedList *m_pPrev;		///< Pointer to the previous entry
public:
	DoublyLinkedList() { m_pNext = this; m_pPrev = this; }
	~DoublyLinkedList() { Detach(); }
	BURGER_INLINE void Detach(void) {
		DoublyLinkedList *pNext = m_pNext;
		DoublyLinkedList *pPrev = m_pPrev;
		pPrev->m_pNext = pNext;
		pNext->m_pPrev = pPrev;
		m_pNext = this;
		m_pPrev = this;
	}
	BURGER_INLINE void InsertAfter(DoublyLinkedList *pInput) {
		DoublyLinkedList *pNext = pInput->m_pNext;
		DoublyLinkedList *pPrev = pInput->m_pPrev;
		pPrev->m_pNext = pNext;		// Detach the object
		pNext->m_pPrev = pPrev;
		pNext = m_pNext;			// Link in
		pInput->m_pPrev = this;
		pInput->m_pNext = pNext;
		pNext->m_pPrev = pInput;
		m_pNext = pInput;
	}
	BURGER_INLINE void InsertBefore(DoublyLinkedList *pInput) {
		DoublyLinkedList *pNext = pInput->m_pNext;
		DoublyLinkedList *pPrev = pInput->m_pPrev;
		pPrev->m_pNext = pNext;		// Detach the object
		pNext->m_pPrev = pPrev;
		pPrev = m_pPrev;			// Link in
		pInput->m_pPrev = pPrev;
		pInput->m_pNext = this;
		pPrev->m_pNext = pInput;
		m_pPrev = pInput;
	}
	BURGER_INLINE DoublyLinkedList *GetNext(void) const { return m_pNext; }
	BURGER_INLINE DoublyLinkedList *GetPrevious(void) const { return m_pPrev; }
	static DoublyLinkedList * BURGER_API New(void);
};
}
namespace Burger {
class LinkedListPointer : public DoublyLinkedList {
	void *m_pData;			///< Pointer to the data
public:
	LinkedListPointer() : DoublyLinkedList(), m_pData(NULL) {}
	LinkedListPointer(void *pData) : DoublyLinkedList(), m_pData(pData) {}
	BURGER_INLINE LinkedListPointer *GetNext(void) const { return static_cast<LinkedListPointer *>(DoublyLinkedList::GetNext()); }
	BURGER_INLINE LinkedListPointer *GetPrevious(void) const { return static_cast<LinkedListPointer *>(DoublyLinkedList::GetPrevious()); }
	BURGER_INLINE void *GetData(void) const { return m_pData; }
	BURGER_INLINE void SetData(void *pInput) { m_pData = pInput; }
	static LinkedListPointer * BURGER_API New(void *pInput = NULL);
};
extern void BURGER_API Delete(const LinkedListPointer *pInput);
}
namespace Burger {
class LinkedListObjects {
public:
	enum {
		CONTINUE = 0,		///< Don't do anything
		ABORT = 1,			///< Abort iteration
		DELETEOBJECT = 2	///< Delete this object and continue iterating
	};
	typedef Word (BURGER_API *ProcAction)(void *);
	class Object : private DoublyLinkedList {
	friend class LinkedListObjects;
	public:
		typedef void (BURGER_API *ProcDataDelete)(Object *);
		static void BURGER_API ProcNull(Object *pObject);
		static void BURGER_API ProcFreeObjectAndData(Object *pObject);
		static void BURGER_API ProcFreeData(Object *pObject);
		static void BURGER_API ProcFreeObject(Object *pObject);
	private:
		void *m_pData;						///< Pointer to the data
		ProcDataDelete m_ProcDataDelete;	///< Data destructor
	public:
		Object() : DoublyLinkedList(), m_pData(NULL), m_ProcDataDelete(ProcFreeData) {}
		Object(void *pData,ProcDataDelete pDataDelete=ProcFreeData) : DoublyLinkedList(), m_pData(pData), m_ProcDataDelete(pDataDelete) {}
		~Object() { Destroy(); }
	private:
		void Destroy(void);
		BURGER_INLINE void InsertBefore(Object *pObject) { static_cast<DoublyLinkedList *>(this)->InsertBefore(pObject); }
		BURGER_INLINE void InsertAfter(Object *pObject) { static_cast<DoublyLinkedList *>(this)->InsertAfter(pObject); }
	public:
		static Object * BURGER_API New(void *pData,ProcDataDelete pProc=ProcFreeObjectAndData);
		BURGER_INLINE Object *GetNext(void) const { return static_cast<Object *>(static_cast<const DoublyLinkedList *>(this)->GetNext()); }
		BURGER_INLINE Object *GetPrevious(void) const { return static_cast<Object *>(static_cast<const DoublyLinkedList *>(this)->GetPrevious()); }
		BURGER_INLINE void *GetData(void) const { return m_pData; }
		BURGER_INLINE void SetData(void *pInput) { m_pData = pInput; }
		BURGER_INLINE ProcDataDelete GetDataDeleteProc(void) const { return m_ProcDataDelete; }
		BURGER_INLINE void SetDataDeleteProc(ProcDataDelete pProc) { m_ProcDataDelete = pProc; }
	};
private:
	Object *m_pRoot;		///< Root linked list entry
	Word m_uCount;			///< Number of objects in the list
public:
	LinkedListObjects() : m_pRoot(NULL),m_uCount(0) {}
	~LinkedListObjects() { Destroy(); }
	void Destroy(void);
	BURGER_INLINE Word GetCount(void) const { return m_uCount; }
	BURGER_INLINE Object *GetFirst(void) const { return m_pRoot; }
	Object *GetLast(void) const;
	void *GetFirstData(void) const;
	void *GetLastData(void) const;
	void *GetData(Word uIndex) const;
	Object *GetObject(Word uIndex) const;
	Object *GetObject(void *pData) const;
	Object *GetStringObject(const char *pString) const;
	Word GetStringIndex(const char *pString) const;
	void DestroyObject(Object *pObject);
	void AppendObject(Object *pObject);
	void PrependObject(Object *pObject);
	void AppendObject(void *pData,Object::ProcDataDelete pDataDelete=Object::ProcFreeObjectAndData);
	void PrependObject(void *pData,Object::ProcDataDelete pDataDelete=Object::ProcFreeObjectAndData);
	void AppendObject(const char *pString);
	void PrependObject(const char *pString);
	Object *IterateForward(ProcAction pProc);
	Object *IterateReverse(ProcAction pProc);
};
}
namespace Burger {
class NumberString {
private:
	char m_Data[32];		///< String buffer
public:
	NumberString() { m_Data[0] = 0; }
	NumberString(Word32 uInput);
	NumberString(Word32 uInput,Word uFormat);
	NumberString(Int32 iInput);
	NumberString(Int32 iInput,Word uFormat);
	NumberString(Word64 uInput);
	NumberString(Word64 uInput,Word uFormat);
	NumberString(Int64 iInput);
	NumberString(Int64 iInput,Word uFormat);
	NumberString(float fInput);
	NumberString(double dInput);
	NumberString & operator = (Word32 uInput);
	NumberString & operator = (Int32 iInput);
	NumberString & operator = (Word64 uInput);
	NumberString & operator = (Int64 iInput);
	NumberString & operator = (float fInput);
	NumberString & operator = (double dInput);
	BURGER_INLINE operator const char *() const { return m_Data; }
	BURGER_INLINE const char *GetPtr(void) const { return m_Data; }
	BURGER_INLINE char operator[](WordPtr uIndex) const { return m_Data[uIndex]; }
	BURGER_INLINE const char &operator[](WordPtr uIndex) { return m_Data[uIndex]; }
	BURGER_INLINE void Clear(void) { m_Data[0] = 0; }
	BURGER_INLINE Word IsEmpty(void) const { return !m_Data[0]; }
	BURGER_INLINE WordPtr GetLength(void) const { return StringLength(m_Data); }
};
}
namespace Burger {
class NumberStringHex {
private:
	char m_Data[32];		///< String buffer
public:
	NumberStringHex() { m_Data[0] = 0; }
	NumberStringHex(Word32 uInput);
	NumberStringHex(Word32 uInput,Word uFormat);
	NumberStringHex(Word64 uInput);
	NumberStringHex(Word64 uInput,Word uFormat);
	NumberStringHex(float fInput);
	NumberStringHex(double dInput);
	NumberStringHex & operator = (Word32 uInput);
	NumberStringHex & operator = (Word64 uInput);
	NumberStringHex & operator = (float fInput);
	NumberStringHex & operator = (double dInput);
	BURGER_INLINE operator const char *() const { return m_Data; }
	BURGER_INLINE const char *GetPtr(void) const { return m_Data; }
	BURGER_INLINE char operator[](WordPtr uIndex) const { return m_Data[uIndex]; }
	BURGER_INLINE const char &operator[](WordPtr uIndex) { return m_Data[uIndex]; }
	BURGER_INLINE void Clear(void) { m_Data[0] = 0; }
	BURGER_INLINE Word IsEmpty(void) const { return !m_Data[0]; }
	BURGER_INLINE WordPtr GetLength(void) const { return Burger::StringLength(m_Data); }
};
}
namespace Burger {
class SimpleString {
private:
	const char *m_pData;		///< Pointer to the actual string, never is \ref NULL
public:
	SimpleString(void) : m_pData(Burger::g_EmptyString) {}
	SimpleString(char cInput);
	SimpleString(const char *pInput1);
	SimpleString(const char *pInput1,const char *pInput2);
	SimpleString(const char *pInput1,const char *pInput2,const char *pInput3);
	SimpleString(const char *pInput1,const char *pInput2,const char *pInput3,const char *pInput4);
	SimpleString(const char *pInput1,const char *pInput2,const char *pInput3,const char *pInput4,const char *pInput5);
	SimpleString(const Burger::SimpleString &rInput);
	~SimpleString();
	Burger::SimpleString & operator = (char cInput);
	Burger::SimpleString & operator = (const char *pInput);
	Burger::SimpleString & operator = (const Burger::SimpleString &rInput);
	BURGER_INLINE operator const char *() const { return m_pData; }
	BURGER_INLINE const char *GetPtr(void) const { return m_pData; }
	BURGER_INLINE char operator[](WordPtr uIndex) const { return m_pData[uIndex]; }
	BURGER_INLINE const char &operator[](WordPtr uIndex) { return m_pData[uIndex]; }
	void BURGER_API Clear(void);
	BURGER_INLINE Word IsEmpty(void) const { return !m_pData[0]; }
	BURGER_INLINE WordPtr GetLength(void) const { return Burger::StringLength(m_pData); }
};
}
namespace Burger {
class Filename;
struct RGBAWord8_t;
struct RGBWord8_t;
class InputMemoryStream {
	const Word8 *m_pWork;			///< Pointer to the input
	const Word8 *m_pEndOfBuffer;	///< Pointer to the end of the buffer
	const Word8 *m_pData;			///< Pointer to the first data buffer
	WordPtr m_uBufferSize;			///< Size of the buffer
	Word m_bDontFree;				///< \ref TRUE if the memory isn't released on Clear()
	BURGER_DISABLECOPYCONSTRUCTORS(InputMemoryStream);
public:
	InputMemoryStream();
	InputMemoryStream(const char *pFilename);
	InputMemoryStream(const void *pBuffer,WordPtr uBufferSize,Word bDontFree=FALSE);
	~InputMemoryStream();
	Word BURGER_API Open(const char *pFilename);
	Word BURGER_API Open(Filename *pFilename);
	void BURGER_API Open(const void *pBuffer,WordPtr uBufferSize,Word bDontFree=FALSE);
	void BURGER_API Clear(void);
	void BURGER_API SkipForward(WordPtr uOffset);
	void BURGER_API SkipBack(WordPtr uOffset);
	void BURGER_API SetMark(WordPtr uOffset);
	BURGER_INLINE const Word8 * GetPtr(void) const { return m_pWork; }
	BURGER_INLINE WordPtr GetMark(void) const { return static_cast<WordPtr>(m_pWork-m_pData); }
	BURGER_INLINE WordPtr GetSize(void) const { return m_uBufferSize; }
	BURGER_INLINE Word IsEmpty(void) const { return m_pWork>=m_pEndOfBuffer; }
	BURGER_INLINE WordPtr BytesRemaining(void) const { return static_cast<WordPtr>(m_pEndOfBuffer-m_pWork); }
	void BURGER_API GetString(char *pOutput,WordPtr uOutputSize);
	void BURGER_API GetString(String *pOutput);
	void BURGER_API GetCString(char *pOutput,WordPtr uOutputSize);
	void BURGER_API GetPString(char *pOutput,WordPtr uOutputSize);
	Word8 BURGER_API GetByte(void);
	Word16 BURGER_API GetShort(void);
	Word16 BURGER_API GetBigShort(void);
	Word32 BURGER_API GetWord32(void);
	Word32 BURGER_API GetBigWord32(void);
	float BURGER_API GetFloat(void);
	float BURGER_API GetBigFloat(void);
	double BURGER_API GetDouble(void);
	double BURGER_API GetBigDouble(void);
	WordPtr BURGER_API Get(void *pOutput,WordPtr uOutputSize);
	Word BURGER_API Get(RGBWord8_t *pOutput);
	Word BURGER_API Get(RGBAWord8_t *pOutput);
	Word BURGER_API Get(Vector2D_t *pOutput);
	Word BURGER_API Get(Vector3D_t *pOutput);
	Word BURGER_API Get(Vector4D_t *pOutput);
	void BURGER_API ParseBeyondWhiteSpace(void);
	Word BURGER_API IsStringMatch(const char *pInput);
	Word BURGER_API IsStringMatchCase(const char *pInput);
	Word BURGER_API IsDataMatch(const Word8 *pInput,WordPtr uLength);
};
}
namespace Burger {
class OutputMemoryStream {
	enum {
		CHUNKSIZE = 0x40000-static_cast<int>(sizeof(Word8 *))	///< Size of each data chunk
	};
	Word8 *m_pData;		///< Pointer to the first data buffer
	Word8 *m_pWork;		///< Pointer to the current buffer
	WordPtr m_uIndex;	///< Current file mark
	BURGER_DISABLECOPYCONSTRUCTORS(OutputMemoryStream);
public:
	OutputMemoryStream();
	~OutputMemoryStream();
	void BURGER_API Clear(void);
	WordPtr BURGER_API GetSize(void) const;
	Word BURGER_API IsEmpty(void) const;
	Word BURGER_API SaveFile(const char *pFilename) const;
	Word BURGER_API SaveFile(Filename *pFilename) const;
	Word BURGER_API Save(String *pOutput) const;
	Word BURGER_API Flatten(void *pOutput,WordPtr uLength) const;
	void *BURGER_API Flatten(WordPtr *pLength) const;
	Word BURGER_API Append(char iChar);
	Word BURGER_API Append(const char *pString);
	Word BURGER_API AppendPString(const char *pString);
	Word BURGER_API Append(Word8 uByte);
	Word BURGER_API Append(Word16 uShort);
	Word BURGER_API Append(Word32 uWord);
	Word BURGER_API Append(Word64 uWord);
	Word BURGER_API Append(const void *pData,WordPtr uSize);
	Word BURGER_API AppendAscii(Word32 uInput);
	Word BURGER_API AppendAscii(Word64 uInput);
	Word BURGER_API AppendAscii(Int32 iInput);
	Word BURGER_API AppendAscii(Int64 iInput);
	Word BURGER_API AppendAscii(float fInput);
	Word BURGER_API AppendAscii(double dInput);
	Word BURGER_API AppendTabs(Word uTabCount);
	Word BURGER_API Compare(const void *pInput,WordPtr uLength) const;
	Word BURGER_API Overwrite(const void *pInput,WordPtr uLength,WordPtr uOffset);
};
}
struct timespec;
namespace Burger {
struct TimeDate_t {
	Word32 m_uYear;				///< Year "2009"
	Word16 m_usMilliseconds;	///< 0-999
	Word8 m_bMonth;				///< 1-12
	Word8 m_bDay;				///< 1-31
	Word8 m_bDayOfWeek;			///< 0-6
	Word8 m_bHour;				///< 0-23
	Word8 m_bMinute;			///< 0-59
	Word8 m_bSecond;			///< 0-59
	void Clear(void);
	void GetTime(void);
	void TimeToString(char *pOutput) const;
	void TimeToStringPM(char *pOutput) const;
	void DateToString(char *pOutput) const;
	void DateToStringVerbose(char *pOutput) const;
	Word Read(Burger::InputMemoryStream *pInput);
	Word Write(Burger::OutputMemoryStream *pOutput) const;
	int Compare(const TimeDate_t *pInput) const;
	BURGER_INLINE friend Word operator == (const TimeDate_t &rInput1,const TimeDate_t &rInput2) { return rInput1.Compare(&rInput2)==0; }
	BURGER_INLINE friend Word operator != (const TimeDate_t &rInput1,const TimeDate_t &rInput2) { return rInput1.Compare(&rInput2)!=0; }
	BURGER_INLINE friend Word operator > (const TimeDate_t &rInput1,const TimeDate_t &rInput2) { return rInput1.Compare(&rInput2)>0; }
	BURGER_INLINE friend Word operator >= (const TimeDate_t &rInput1,const TimeDate_t &rInput2) { return rInput1.Compare(&rInput2)>=0; }
	BURGER_INLINE friend Word operator < (const TimeDate_t &rInput1,const TimeDate_t &rInput2) { return rInput1.Compare(&rInput2)<0; }
	BURGER_INLINE friend Word operator <= (const TimeDate_t &rInput1,const TimeDate_t &rInput2) { return rInput1.Compare(&rInput2)<=0; }
	Word LoadTimeT(WordPtr uTimeT);
	Word StoreTimeT(WordPtr *pTimeT) const;
	Word Load(const timespec *pTimeSpec);
	Word Store(timespec *pTimeSpec) const;
#if defined(BURGER_WINDOWS) || defined(BURGER_XBOX360) || defined(DOXYGEN)
	Word Load(const _FILETIME *pFileTime);
	Word Store(_FILETIME *pFileTime) const;
#endif
#if defined(BURGER_MSDOS) || defined(DOXYGEN)
	void LoadMSDOS(Word32 uMSDOSTime);
	Word32 StoreMSDOS(void) const;
#endif
#if defined(BURGER_MACOS) || defined(DOXYGEN)
	Word Load(const UTCDateTime *pUTCDateTime);
	Word Store(UTCDateTime *pUTCDateTime) const;
#endif
#if defined(BURGER_MACOSX) || defined(BURGER_IOS) || defined(DOXYGEN)
	Word Load(double dNSTimeInterval);
	Word Store(double *pNSTimeInterval) const;
#endif
#if defined(BURGER_VITA) || defined(DOXYGEN)
	Word Load(const SceDateTime *pSceDateTime);
	Word Store(SceDateTime *pSceDateTime) const;
#endif
};
}
namespace Burger {
class Tick {
	static Word32 s_LastTick;				///< Previously set tick value
public:
	static const Word TICKSPERSEC=60;		///< Number of ticks per second
	static Word32 BURGER_API Read(void);
	static BURGER_INLINE Word32 ResetLastTick(void) { Word32 uTick=Read(); s_LastTick=uTick; return uTick; }
	static BURGER_INLINE Word32 GetLastTick(void) { return s_LastTick; }
	static BURGER_INLINE void WaitOneTick(void) { s_LastTick=Read(); Wait(); }
	static void BURGER_API Wait(Word uCount=1);
	static Word BURGER_API WaitEvent(Word uCount=0);
	static Word32 BURGER_API ReadMicroseconds(void);
	static Word32 BURGER_API ReadMilliseconds(void);
};
enum {
	SLEEP_YIELD=0,					///< Used by Sleep(Word32) to yield the current time quantum
	SLEEP_INFINITE=0xFFFFFFFFU		///< Used by Sleep(Word32) for an infinite time delay
};
extern void BURGER_API Sleep(Word32 uMilliseconds);
}
namespace Burger {
class Filename {
public:
	enum {
		MAXBUFFERSIZE = 256,	///< Size of the filename buffer (Maximum)
#if defined(BURGER_MAC)
		BUFFERSIZE = MAXBUFFERSIZE-static_cast<int>(sizeof(char *)+sizeof(long)+sizeof(short))	///< Size of the filename buffer (Adjusted to to keep the class size at exactly 512 bytes in length)
#else
		BUFFERSIZE = static_cast<int>(MAXBUFFERSIZE-sizeof(char *))		///< Size of the filename buffer (Adjusted to to keep the class size at exactly 512 bytes in length)
#endif
	};
private:
	char *m_pFilename;				///< Pointer to the burgerlib filename
	char *m_pNativeFilename;		///< Pointer to the native filename
#if defined(BURGER_MAC)
	Word8 m_FSRef[80];				///< Opaque FSRef used by MacOS
	long m_lDirID;					///< Directory reference (MacOS Only)
	short m_sVRefNum;				///< Volume reference used by copy and rename  (MacOS Only)
#endif
	char m_Filename[BUFFERSIZE];	///< Local buffer containing the filename (If it can fit in this buffer)
#if !defined(BURGER_MAC) && !defined(DOXYGEN)
	char m_NativeFilename[MAXBUFFERSIZE-(sizeof(char *))];	///< Local buffer containing the native filename
#else
	char m_NativeFilename[MAXBUFFERSIZE-(sizeof(char *)+80)];	///< Local buffer containing the native filename
	static const Word DIRCACHESIZE = 8;	///<  Number of cache entries
	struct ExpandCache_t {
		const char *m_pName;		///< Pointer to the original directory name
		Word32 m_uHitTick;			///< Last time hit (For purging)
		Word m_uNameLength;			///< Length of the string
		Word8 m_FSRef[80];			///< Opaque FSRef
	};
	static ExpandCache_t m_DirectoryCache[DIRCACHESIZE];	///< Directory cache (MAC Classic/Carbon Only)
public:
	static void BURGER_API InitDirectoryCache(void);
	static void BURGER_API PurgeDirectoryCache(void);
#endif
public:
	Filename() : m_pFilename(m_Filename), m_pNativeFilename(m_NativeFilename)
#if defined(BURGER_MAC)
	,m_lDirID(0),m_sVRefNum(0)
#endif
	{ m_Filename[0] = 0; }
	Filename(const char *pFilename);
	Filename(Filename const &rInput);
	Filename & operator = (Filename const &rInput);
	~Filename();
	BURGER_INLINE const char *GetPtr(void) const { return m_pFilename; }
	BURGER_INLINE char *GetPtr(void) { return m_pFilename; }
	void BURGER_API Set(const char *pInput);
	void BURGER_API Clear(void);
	void BURGER_API Append(const char *pInput);
	void BURGER_API GetFileName(char *pOutput,WordPtr uOutputLength) const;
	void BURGER_API GetFileExtension(char *pOutput,WordPtr uOutputLength) const;
	void BURGER_API SetFileExtension(const char *pExtension);
	void BURGER_API DirName(void);
	void BURGER_API DirName(String *pOutput) const;
	void BURGER_API BaseName(String *pOutput) const;
	Word BURGER_API IsFullPathname(void) const;
	Word BURGER_API IsFilenameOnly(void) const;
	Word BURGER_API ParsePrefixNumber(void) const;
	void BURGER_API Expand(void);
	void BURGER_API Expand(const char *pInput);
	const char * BURGER_API GetNative(void);
#if !defined(BURGER_MAC) || defined(DOXYGEN)
	void BURGER_API SetFromNative(const char *pInput);
#endif
#if defined(BURGER_MAC) || defined(DOXYGEN)
	void BURGER_API SetFromNative(const char *pInput,long lDirID=0,short sVRefNum=0);
	BURGER_INLINE FSRef *GetFSRef(void) { return reinterpret_cast<FSRef *>(m_FSRef); }
	BURGER_INLINE long GetDirID(void) const { return m_lDirID; }
	BURGER_INLINE short GetVRefNum(void) const { return m_sVRefNum; }
	BURGER_INLINE void SetDirID(long lDirID) { m_lDirID = lDirID; }
	BURGER_INLINE void SetVRefNum(short sVRefNum) { m_sVRefNum = sVRefNum; }
	Word BURGER_API SetFromDirectoryID(long lDirID,short sVolRefNum);
#endif
};
}
namespace Burger {
extern Word BURGER_API WriteBig(FILE *fp,Word16 uInput);
extern Word BURGER_API WriteBig(FILE *fp,Word32 uInput);
extern Word BURGER_API WriteBig(FILE *fp,Word64 uInput);
extern Word BURGER_API WriteBig(FILE *fp,float fInput);
extern Word BURGER_API WriteBig(FILE *fp,double dInput);
extern Word BURGER_API WriteLittle(FILE *fp,Word16 uInput);
extern Word BURGER_API WriteLittle(FILE *fp,Word32 uInput);
extern Word BURGER_API WriteLittle(FILE *fp,Word64 uInput);
extern Word BURGER_API WriteLittle(FILE *fp,float fInput);
extern Word BURGER_API WriteLittle(FILE *fp,double dInput);
extern Word BURGER_API WriteCString(FILE *fp,const char *pInput);
extern Word16 BURGER_API ReadBigWord16(FILE *fp);
extern Word32 BURGER_API ReadBigWord32(FILE *fp);
extern Word64 BURGER_API ReadBigWord64(FILE *fp);
extern float BURGER_API ReadBigFloat(FILE *fp);
extern double BURGER_API ReadBigDouble(FILE *fp);
extern Word16 BURGER_API ReadLittleWord16(FILE *fp);
extern Word32 BURGER_API ReadLittleWord32(FILE *fp);
extern Word64 BURGER_API ReadLittleWord64(FILE *fp);
extern float BURGER_API ReadLittleFloat(FILE *fp);
extern double BURGER_API ReadLittleDouble(FILE *fp);
extern Word BURGER_API ReadCString(FILE *fp,char *pInput,WordPtr uLength);
extern WordPtr BURGER_API GetSize(FILE *fp);
extern Word64 BURGER_API GetSize64(FILE *fp);
extern Word BURGER_API SaveFile(FILE *fp,const void *pData,WordPtr uLength);
extern void * BURGER_API LoadFile(FILE *fp,WordPtr *uLength);
}
namespace Burger {
struct FileManager {
public:
	enum {
		PREFIXCURRENT=8,		///< 8: Current working directory at application launch
		PREFIXAPPLICATION=9,	///< 9: Directory where the application executable resides
		PREFIXBOOT=32,			///< "*:" Boot volume prefix number
		PREFIXPREFS=33,			///< "@:" User preferences folder prefix number
		PREFIXSYSTEM=34,		///< "$:" System volume folder prefix number
		PREFIXMAX=35,			///< Maximum number of pathname prefixes
		PREFIXINVALID=999		///< Illegal prefix number
	};
static void BURGER_API Init(void);
static void BURGER_API Shutdown(void);
#if defined(BURGER_MSDOS)
static Word BURGER_API AreLongFilenamesAllowed(void);
#else
static BURGER_INLINE Word AreLongFilenamesAllowed(void) { return TRUE; }
#endif
static Word BURGER_API GetVolumeName(Filename *pOutput,Word uVolumeNum);
static Word BURGER_API GetVolumeNumber(const char *pInput);
static void BURGER_API DefaultPrefixes(void);
static Word BURGER_API GetPrefix(Filename *pOutput,Word uPrefixNum);
static Word BURGER_API SetPrefix(Word uPrefixNum,const char *pPrefixName);
static Word BURGER_API SetPrefix(Word uPrefixNum,Filename *pPrefixName);
static void BURGER_API PopPrefix(Word uPrefixNum);
static Word BURGER_API GetModificationTime(const char *pFileName,TimeDate_t *pOutput);
static Word BURGER_API GetModificationTime(Filename *pFileName,TimeDate_t *pOutput);
static Word BURGER_API GetCreationTime(const char *pFileName,TimeDate_t *pOutput);
static Word BURGER_API GetCreationTime(Filename *pFileName,TimeDate_t *pOutput);
static Word BURGER_API DoesFileExist(const char *pFileName);
static Word BURGER_API DoesFileExist(Filename *pFileName);
static Word32 BURGER_API GetAuxType(const char *pFileName);
static Word32 BURGER_API GetAuxType(Filename *pFileName);
static Word32 BURGER_API GetFileType(const char *pFileName);
static Word32 BURGER_API GetFileType(Filename *pFileName);
static Word BURGER_API GetFileAndAuxType(const char *pFileName,Word32 *pFileType,Word32 *pAuxType);
static Word BURGER_API GetFileAndAuxType(Filename *pFileName,Word32 *pFileType,Word32 *pAuxType);
static Word BURGER_API SetAuxType(const char *pFileName,Word32 uAuxType);
static Word BURGER_API SetAuxType(Filename *pFileName,Word32 uAuxType);
static Word BURGER_API SetFileType(const char *pFileName,Word32 uFileType);
static Word BURGER_API SetFileType(Filename *pFileName,Word32 uFileType);
static Word BURGER_API SetFileAndAuxType(const char *pFileName,Word32 uFileType,Word32 uAuxType);
static Word BURGER_API SetFileAndAuxType(Filename *pFileName,Word32 uFileType,Word32 uAuxType);
static Word BURGER_API CreateDirectoryPath(const char *pFileName);
static Word BURGER_API CreateDirectoryPath(Filename *pFileName);
static Word BURGER_API CreateDirectoryPathDirName(const char *pFileName);
static Word BURGER_API CreateDirectoryPathDirName(Filename *pFileName);
static Word BURGER_API DeleteFile(const char *pFileName);
static Word BURGER_API DeleteFile(Filename *pFileName);
static Word BURGER_API RenameFile(const char *pNewName,const char *pOldName);
static Word BURGER_API RenameFile(Filename *pNewName,Filename *pOldName);
static Word BURGER_API ChangeOSDirectory(const char *pDirName);
static Word BURGER_API ChangeOSDirectory(Filename *pDirName);
static FILE *BURGER_API OpenFile(const char *pFileName,const char *pType);
static FILE *BURGER_API OpenFile(Filename *pFileName,const char *pType);
static Word BURGER_API CopyFile(const char *pDestName,const char *pSourceName);
static Word BURGER_API CopyFile(Filename *pDestName,Filename *pSourceName);
static Word BURGER_API SaveFile(const char *pFileName,const void *pData,WordPtr uLength);
static Word BURGER_API SaveFile(Filename *pFileName,const void *pData,WordPtr uLength);
static Word BURGER_API SaveTextFile(const char *pFileName,const void *pData,WordPtr uLength);
static Word BURGER_API SaveTextFile(Filename *pFileName,const void *pData,WordPtr uLength);
static void * BURGER_API LoadFile(const char *pFileName,WordPtr *pLength);
static void * BURGER_API LoadFile(Filename *pFileName,WordPtr *pLength);
#if (defined(BURGER_MACOSX) || defined(BURGER_IOS)) || defined(DOXYGEN)
static BURGER_INLINE const char *GetBootName(void) { return g_FileManager.m_pBootName; }
static BURGER_INLINE Word GetBootNameSize(void) { return g_FileManager.m_uBootNameSize; }
#endif
private:
	void ReleasePrefixes(void);
	const char *m_pPrefix[PREFIXMAX];	///< Array of prefix strings
#if defined(BURGER_MSDOS) || defined(DOXYGEN)
	Word8 m_bAllowed;					///< True if MSDOS has long filename support (MSDOS Only)
#endif
#if (defined(BURGER_MACOSX) || defined(BURGER_IOS)) || defined(DOXYGEN)
	Word m_uBootNameSize;	///< Length of the boot volume name (MACOSX or iOS only)
	char *m_pBootName;		///< Boot volume name in the format ":FooBar" (Zero terminated) (MACOSX or iOS only)
#endif
	static FileManager g_FileManager;	///< Global instance of the file manager
};
class FileManagerSimple {
public:
	FileManagerSimple() { Burger::FileManager::Init(); }
	~FileManagerSimple() { Burger::FileManager::Shutdown(); }
};
}
namespace Burger {
class File {
public:
	enum eFileAccess {
		READONLY=0x00,		///< Open file with read access only
		WRITEONLY=0x01,		///< Create and open empty file with write access only
		APPEND=0x02,		///< Open file with write access and set the mark at the end
		READANDWRITE=0x3	///< Open file for read and write access
	};
	enum {
		OKAY=0,				///< No error
		NOT_IMPLEMENTED=1,	///< Requested task not available on this platform
		IOERROR=2,			///< Device error
		WRITEERROR=3,		///< Can't write (Writing to a DVD?)
		INVALID_MARK=4,		///< File mark beyond the range of the file
		OUTOFRANGE=5,		///< Parameter out of range
		FILENOTFOUND=6		///< File not found
	};
	File();
	File(const char *pFileName,eFileAccess eAccess=READONLY);
	File(Filename *pFileName,eFileAccess eAccess=READONLY);
	~File();
	static File * BURGER_API New(const char *pFileName,eFileAccess eAccess=READONLY);
	static File * BURGER_API New(Filename *pFileName,eFileAccess eAccess=READONLY);
	BURGER_INLINE Word IsOpened(void) const { return m_pFile!=NULL; }
	Word Open(const char *pFileName,eFileAccess eAccess=READONLY);
	Word Open(Filename *pFileName,eFileAccess eAccess=READONLY);
	Word Close(void);
	WordPtr GetSize(void);
	WordPtr Read(void *pOutput,WordPtr uSize);
	WordPtr Write(const void *pInput,WordPtr uSize);
	WordPtr GetMark(void);
	Word SetMark(WordPtr uMark);
	Word SetMarkAtEOF(void);
	Word GetModificationTime(TimeDate_t *pOutput);
	Word GetCreationTime(TimeDate_t *pOutput);
	Word SetModificationTime(const TimeDate_t *pInput);
	Word SetCreationTime(const TimeDate_t *pInput);
#if (defined(BURGER_MACOS) || defined(BURGER_IOS)) || defined(DOXYGEN)
	Word SetAuxType(Word32 uAuxType);
	Word SetFileType(Word32 uFileType);
	Word32 GetAuxType(void);
	Word32 GetFileType(void);
	Word SetAuxAndFileType(Word32 uAuxType,Word32 uFileType);
#else
	BURGER_INLINE Word SetAuxType(Word32 /* uAuxType */) { return NOT_IMPLEMENTED; }
	BURGER_INLINE Word SetFileType(Word32 /* uFileType */) { return NOT_IMPLEMENTED; }
	BURGER_INLINE Word32 GetAuxType(void) const { return 0; }
	BURGER_INLINE Word32 GetFileType(void) const { return 0; }
	BURGER_INLINE Word SetAuxAndFileType(Word32 /* uAuxType */,Word32 /* uFileType */) { return NOT_IMPLEMENTED; }
#endif
	Word ReadCString(char *pOutput,WordPtr uLength);
	Word32 ReadBigWord32(void);
	Word16 ReadBigWord16(void);
	Word32 ReadLittleWord32(void);
	Word16 ReadLittleWord16(void);
private:
	void *m_pFile;				///< Open file reference
#if defined(BURGER_MAC) || defined(DOXYGEN)
	Word8 m_FSRef[80];			///< File reference (MacOS Only)
#endif
};
}
namespace Burger {
class DirectorySearch {
public:
	DirectorySearch();
	~DirectorySearch();
	Word Open(Filename *pDirName);
	Word Open(const char *pDirName);
	Word GetNextEntry(void);
	Word GetNextEntryExtension(const char *pExt);
	void Close(void);
	WordPtr m_uFileSize;	///< Size of the file in bytes (64 bits on 64 bit CPU platforms)
	TimeDate_t m_CreationDate;		///< File creation time
	TimeDate_t m_ModificatonDate;	///< File last modification time
	Word8 m_bDir;			///< True if this is a directory
	Word8 m_bSystem;		///< True if this is a system file
	Word8 m_bHidden;		///< True if this file is hidden
	Word8 m_bLocked;		///< True if this file is read only
	char m_Name[256];		///< UTF8 Filename
#if (defined(BURGER_MACOS) || defined(BURGER_IOS)) || defined(DOXYGEN)
	Word32 m_uFileType;		///< File's type (MacOS and iOS Only)
	Word32 m_uAuxType;		///< File's creator code (MacOS and iOS Only)
#endif
private:
#if defined(BURGER_MAC) || defined(DOXYGEN)
	OpaqueFSIterator* m_pIterator;	///< Directory iterator (MacOS Carbon Only)
#endif
#if (defined(BURGER_MACOSX) || defined(BURGER_IOS) || defined(BURGER_VITA)) || defined(DOXYGEN)
	int m_fp;				///< Open directory file (MacOSX/iOS/Vita Only)
#endif
#if defined(BURGER_MSDOS) || defined(DOXYGEN)
	Word m_bHandleOk;		///< Handle is valid (MSDOS Only)
	short m_sFileHandle;	///< Handle to the open directory (MSDOS Only)
	char m_MyFindT[44];		///< Dos FindT structure (MSDOS Only)
#endif
#if defined(BURGER_WINDOWS) || defined(BURGER_XBOX360) || defined(DOXYGEN)
	void *m_hDirHandle;		///< Windows file handle (Windows or Xbox 360 Only)
	char m_MyFindW[592];	///< Windows WIN32_FIND_DATAW structure (Windows or Xbox 360 Only)
#endif
};
}
#if defined(BURGER_MSDOS) || defined(DOXYGEN)
#ifdef __cplusplus
extern "C" {
#endif
extern void *_x32_zero_base_ptr;		///< Base Pointer to Real memory MSDOS Only
extern Word16 _x32_zero_base_selector;	///< Segment to Real memory MSDOS Only
BURGER_INLINE Word8 *ZeroBase(void) { return static_cast<Word8 *>(_x32_zero_base_ptr); }
extern void BURGER_API CallInt10(Word EAX);
extern Word BURGER_API CallInt14(Word EAX,Word EDX);
extern Word BURGER_API CallInt17(Word EAX,Word EDX);
extern Int32 BURGER_API Int86x(Word32 uInterrupt,const Burger::Regs16 *pInput,Burger::Regs16 *pOutput);
extern void BURGER_API SetBothInts(Word32 uInterrupt,void far *pCode);
extern void BURGER_API SetProtInt(Word32 uInterrupt,void far *pCode);
extern void BURGER_API SetRealInt(Word32 uInterrupt,Word32 pCode);
extern void far * BURGER_API GetProtInt(Word32 uInterrupt);
extern Word32 BURGER_API GetRealInt(Word32 uInterrupt);
extern void * BURGER_API MapPhysicalAddress(void *pInput,Word32 uLength);
extern int BURGER_API CallRealProcX32(Word32 pAddress,const Burger::Regs16 *pInput,Burger::Regs16 *pOutput);
extern void * BURGER_API RealToProtectedPtr(Word32 pReal);
extern void * BURGER_API GetRealBufferProtectedPtr(void);
extern Word32 BURGER_API GetRealBufferPtr(void);
extern Word32 BURGER_API AllocRealMemory(Word32 uSize);
extern void BURGER_API DeallocRealMemory(Word32 pReal);
#ifdef __cplusplus
}
#endif
#endif
namespace Burger {
class AutoRepeat {
private:
	enum {
		HELDDOWNBEFORE=1,	///< \ref TRUE if the button(s) were previously held down
		SECONDDELAY=2,		///< \ref TRUE if secondary delay is active
		WAITFORKEYUP=4,		///< \ref TRUE if pending a key up due to button down on launch
		INITIALIZED=8		///< \ref TRUE if initialized
	};
	Word32 m_uButtons;		///< Bit field of buttons to test against
	Word32 m_uInitialTick;	///< Delay for initial joydown in 1/60ths of a second
	Word32 m_uRepeatTick;	///< Delay for repeater in 1/60ths of a second
	Word32 m_uTimeMark;		///< Internal time mark
	Word m_uFlags;			///< Current state flags
public:
	AutoRepeat(Word32 uButtons,Word32 uInitialTick,Word32 uRepeatTick);
	void Init(Word32 uButtons,Word32 uInitialTick,Word32 uRepeatTick);
	BURGER_INLINE void Reset(void) { m_uFlags = 0; }
	Word IsItRepeating(Word32 uButtons);
};
}
namespace Burger {
class Random {
protected:
	Word32 m_Array[17];	///< Array of seed values (Polynomial)
	Word32 m_uSeed;		///< Random number seed
	Word m_uIndex;		///< First lookup index
public:
	BURGER_INLINE Random() { Init(); }
	static Random* BURGER_API New(Word32 uNewSeed=0);
	void BURGER_API Init(void);
	void BURGER_API RandomInit(void);
	Word32 BURGER_API Get(Word32 uRange=0);
	void BURGER_API SetSeed(Word32 uNewSeed);
	Int32 BURGER_API GetSigned(Word32 uRange);
	float BURGER_API GetFloat(void);
	float BURGER_API GetFloat(float fRange);
	float BURGER_API GetSymmetricFloat(void);
	float BURGER_API GetSymmetricFloat(float fRange);
};
}
namespace Burger {
class RunQueue {
	BURGER_DISABLECOPYCONSTRUCTORS(RunQueue);
public:
	enum eReturnCode {
		OKAY,		///< Executed normally
		ABORT,		///< Error occured that requires an immediate abort
		DISPOSE		///< Dispose of this callback
	};
	enum {
		LOWESTPRIORITY=0,		///< Lowest priority for RunQueue tasks, do not go lower than this value
		LOWPRIORITY=25,			///< Low priority for RunQueue tasks
		MEDIUMPRIORITY=50,		///< Average priority for RunQueue tasks
		HIGHPRIORITY=75,		///< High priority for RunQueue tasks
		HIGHESTPRIORITY=100		///< Highest priority for RunQueue tasks, (Reserved for Burgerlib, do not use or exceed this value)
	};
	typedef eReturnCode (BURGER_API *CallbackProc)(void *);
	RunQueue() : m_pFirst(NULL), m_Recurse(FALSE) {}
	~RunQueue();
	void Call(void);
	Word Add(CallbackProc pProc,void *pData=NULL,Word uPriority=MEDIUMPRIORITY);
	Word Find(CallbackProc pProc) const;
	Word Find(CallbackProc pProc,void *pData) const;
	Word RemoveAll(CallbackProc pProc);
	Word Remove(CallbackProc pProc,void *pData=NULL);
	void Clear(void);
private:
	struct RunQueueEntry_t {
		RunQueueEntry_t *m_pNext;	///< Handle to the next FunctionEntry_t in chain
		CallbackProc m_pProc;		///< Function to call for this entry
		void *m_pData;				///< User supplied data pointer to call the function with
		Word m_uPriority;			///< User supplied priority for inserting a new entry into the list
	};
	RunQueueEntry_t *m_pFirst;	///< Pointer to the first entry
	Word m_Recurse;				///< \ref TRUE if this class is the process of executing.
};
}
namespace Burger {
class DetectMultiLaunch {
	BURGER_DISABLECOPYCONSTRUCTORS(DetectMultiLaunch);
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
	void *m_hInstanceLock;			///< Windows handle to an instance lock (Windows only)
public:
	DetectMultiLaunch();
	~DetectMultiLaunch();
	Word IsMultiLaunched(const char *pSignature);
#else
public:
	BURGER_INLINE Word IsMultiLaunched(const char * /* pSignature */) { return FALSE; }
#endif
};
}
namespace Burger {
class OSCursor;
class OSCursorImage {
	friend class OSCursor;
	BURGER_DISABLECOPYCONSTRUCTORS(OSCursorImage);
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
	HICON__ *m_pCursorImage;	///< Windows only, handle to the cursor image
#endif
	Word m_uWidth;			///< Width of the cursor in pixels
	Word m_uHeight;			///< Height of the cursor in pixels
	Int m_iHotX;			///< Anchor X coordinate of the cursor
	Int m_iHotY;			///< Anchor Y coordinate of the cursor
public:
	OSCursorImage();
	~OSCursorImage();
	Word BURGER_API CreateMonoChromeImage(const Word8 *pXor,const Word8 *pAnd,Word uWidth,Word uHeight,Int iHotX,Int iHotY);
	void BURGER_API Shutdown(void);
};
class OSCursor {
public:
	enum eCursor {
		CURSOR_NONE,	///< No cursor at all
		CURSOR_ARROW,	///< Standard arrow cursor
		CURSOR_IBEAM,	///< Text edit i-beam cursor
		CURSOR_WAIT,	///< Beachball cursor
		CURSOR_CROSS,	///< Crosshairs cursor
		CURSOR_COUNT,	///< Total number of system cursors
		CURSOR_CUSTOM	///< Cursor set by a call with SetImage()
	};
private:
	BURGER_DISABLECOPYCONSTRUCTORS(OSCursor);
#if defined(BURGER_MAC) || defined(DOXYGEN)
	CCrsr **m_pCursorImage;		///< MacOS only, handle to the cursor image
#endif
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
	HICON__ *m_pCursorImage;	///< Windows only, handle to the cursor image
#endif
	eCursor m_eIDNumber;		///< ID Number of the currently set cursor
	Word m_bVisibleFlag;		///< \ref TRUE if the cursor is visible
	Word m_bActiveFlag;			///< \ref TRUE if a game cursor is loaded
	static OSCursor g_Global;
	OSCursor();
public:
	~OSCursor();
	static BURGER_INLINE Word IsVisible(void) { return g_Global.m_bVisibleFlag; }
	static BURGER_INLINE Word IsActive(void) { return g_Global.m_bActiveFlag; }
	static BURGER_INLINE Word GetImageIDNumber(void) { return g_Global.m_eIDNumber; }
	static BURGER_INLINE Word IsThisADesktop(void) {
#if defined(BURGER_WINDOWS) || defined(BURGER_MACOS) || defined(BURGER_LINUX)
		return TRUE;
#else
		return FALSE;
#endif
	}
	static void BURGER_API SetImageFromIDNumber(eCursor eCursorNumber);
	static void BURGER_API SetImage(const OSCursorImage *pImage);
	static Word BURGER_API Show(void);
	static Word BURGER_API Show(Word bVisible);
	static Word BURGER_API Hide(void);
	static void BURGER_API Init(void);
	static void BURGER_API Shutdown(void);
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
	static void BURGER_API Refresh(void);
#endif
};
}
namespace Burger {
struct Point2D_t {
	int	m_iX;		///< X coordinate of the point
	int m_iY;		///< Y coordinate of the point
	BURGER_INLINE int GetX(void) const { return m_iX; }
	BURGER_INLINE int GetY(void) const { return m_iY; }
	BURGER_INLINE int *GetXPtr(void) { return &m_iX; }
	BURGER_INLINE int *GetYPtr(void) { return &m_iY; }
	BURGER_INLINE void SetX(int iX) { m_iX = iX; }
	BURGER_INLINE void SetY(int iY) { m_iY = iY; }
	BURGER_INLINE void Set(int iX,int iY) { m_iX = iX; m_iY = iY; }
	BURGER_INLINE void Clear(void) { m_iX = 0; m_iY = 0; }
	Word Read(FILE *fp);
	Word Write(FILE *fp) const;
	Word Read(Burger::File *fp);
	Word Write(Burger::File *fp) const;
#if (defined(BURGER_MACOS)) || defined(DOXYGEN)
	void Get(Point *pOutput) const;
	void Set(const Point *pInput);
#endif
#if (defined(BURGER_MACOSX) || defined(BURGER_IOS)) || defined(DOXYGEN)
	void Get(CGPoint *pOutput) const;
	void Set(const CGPoint *pInput);
#if (!defined(BURGER_64BITCPU) && defined(BURGER_MACOSX)) || defined(DOXYGEN)
	void Get(_NSPoint *pOutput) const;
	void Set(const _NSPoint *pInput);
#endif
#endif
#if (defined(BURGER_WINDOWS) || defined(BURGER_XBOX360)) || defined(DOXYGEN)
	void Get(tagPOINT *pOutput) const;
	void Set(const tagPOINT *pInput);
#endif
};
}
namespace Burger {
struct Rect_t {
	int m_iLeft;	///< Leftmost x of rectangle
	int m_iTop;		///< Topmost y of rectangle
	int m_iRight;	///< Rightmost x of rectangle
	int m_iBottom;	///< Bottommost y of rectangle
	BURGER_INLINE int GetWidth(void) const { return (m_iRight-m_iLeft); }
	BURGER_INLINE int GetHeight(void) const { return (m_iBottom-m_iTop); }
	BURGER_INLINE int GetLeft(void) const { return m_iLeft; }
	BURGER_INLINE int GetTop(void) const { return m_iTop; }
	BURGER_INLINE int GetRight(void) const { return m_iRight; }
	BURGER_INLINE int GetBottom(void) const { return m_iBottom; }
	BURGER_INLINE void SetWidth(int iWidth) { m_iRight = m_iLeft+iWidth; }
	BURGER_INLINE void SetHeight(int iHeight) { m_iBottom = m_iTop+iHeight; }
	BURGER_INLINE void SetSize(int iWidth,int iHeight) { m_iRight = m_iLeft+iWidth; m_iBottom = m_iTop+iHeight; }
	BURGER_INLINE void SetLeft(int iLeft) { m_iLeft = iLeft; }
	BURGER_INLINE void SetTop(int iTop) { m_iTop = iTop; }
	BURGER_INLINE void SetRight(int iRight) { m_iRight = iRight; }
	BURGER_INLINE void SetBottom(int iBottom) { m_iBottom = iBottom; }
	BURGER_INLINE void Set(int iLeft,int iTop,int iRight,int iBottom) { m_iLeft = iLeft; m_iTop = iTop; m_iRight = iRight; m_iBottom = iBottom; }
	BURGER_INLINE void SetBySize(int iLeft,int iTop,int iWidth,int iHeight) { m_iLeft = iLeft; m_iTop = iTop; m_iRight = iLeft+iWidth; m_iBottom = iTop+iHeight; }
	BURGER_INLINE void Clear(void) { m_iLeft = 0; m_iTop = 0; m_iRight = 0; m_iBottom = 0; }
	BURGER_INLINE void Offset(int iX,int iY) { m_iLeft+=iX; m_iTop+=iY; m_iRight+=iX; m_iBottom+=iY; }
	void MoveTo(int iX,int iY);
	void MoveTo(const Point2D_t *pInput);
	void MoveX(int iX);
	void MoveY(int iY);
	Word IsInside(int iX,int iY) const;
	Word IsInside(const Point2D_t *pPoint) const;
	Word IsInside(const Rect_t *pRect) const;
	void Sort(void);
	void SetSorted(int iLeft,int iTop,int iRight,int iBottom);
	Word IsEmpty(void) const;
	Word IsNotEmpty(void) const;
	Word IsEqual(const Rect_t *pInput) const;
	Word IsNotEqual(const Rect_t *pInput) const;
	BURGER_INLINE Word operator==(const Rect_t &rInput) const { return IsEqual(&rInput); }
	BURGER_INLINE Word operator!=(const Rect_t &rInput) const { return IsNotEqual(&rInput); }
	void Inset(int iX,int iY);
	Word IsIntersecting(const Rect_t *pInput) const;
	Word Intersection(const Rect_t *pInput1,const Rect_t *pInput2);
	void Union(const Rect_t *pInput1,const Rect_t *pInput2);
	void Add(const Point2D_t *pInput);
	void Add(int iX,int iY);
	void Clip(const Rect_t *pInput);
#if defined(BURGER_MACOS) || defined(DOXYGEN)
	void Get(Rect *pOutput) const;
	void Set(const Rect *pInput);
#endif
#if (defined(BURGER_MACOSX) || defined(BURGER_IOS)) || defined(DOXYGEN)
	void Get(CGRect *pOutput) const;
	void Set(const CGRect *pInput);
#if (!defined(BURGER_64BITCPU) && defined(BURGER_MACOSX)) || defined(DOXYGEN)
	void Get(_NSRect *pOutput) const;
	void Set(const _NSRect *pInput);
#endif
#endif
#if (defined(BURGER_WINDOWS) || defined(BURGER_XBOX360)) || defined(DOXYGEN)
	void Get(tagRECT *pOutput) const;
	void Set(const tagRECT *pInput);
#endif
};
}
namespace Burger {
class CodeLibrary {
	BURGER_DISABLECOPYCONSTRUCTORS(CodeLibrary);
	void *m_pLibInstance;			///< Instance of the code library
public:
	CodeLibrary() : m_pLibInstance(NULL) {}
	~CodeLibrary() { Shutdown(); }
	Word Init(const char *pFilename);
	void Shutdown(void);
	void *GetFunction(const char *pFunctionName);
	BURGER_INLINE Word IsInitialized(void) const { return m_pLibInstance!=NULL; }
};
}
#if (defined(BURGER_WINDOWS) || defined(BURGER_MACOSX)) || defined(DOXYGEN)
namespace Burger {
class Perforce {
	BURGER_DISABLECOPYCONSTRUCTORS(Perforce);
	Filename m_PerforceFilename;		///< Filename for p4 executable file
	Word m_bFilenameInitialized;		///< \ref TRUE if the perforce executable is found
public:
	Perforce();
	~Perforce();
	Word BURGER_API Init(void);
	Word BURGER_API Shutdown(void);
	Word BURGER_API Edit(const char *pFilename);
	Word BURGER_API RevertIfUnchanged(const char *pFilename);
};
}
#else
namespace Burger {
class Perforce {
	BURGER_DISABLECOPYCONSTRUCTORS(Perforce);
public:
	BURGER_INLINE Word Init(void) const { return 20; }
	BURGER_INLINE Word Shutdown(void) const { return 20; }
	BURGER_INLINE Word Edit(const char * /* pFilename */) const { return 20; }
	BURGER_INLINE Word RevertIfUnchanged(const char * /* pFilename */) const { return 20; }
};
}
#endif
namespace Burger {
class ConsoleApp : public Burger::Base {
	BURGER_DISABLECOPYCONSTRUCTORS(ConsoleApp);
	MemoryManagerGlobalANSI m_ANSIMemoryManager;	///< Use ANSI memory manager for tools
	const char **m_ppArgv;	///< Arguments passed to the console
	int m_iArgc;			///< Number of valid arguments
	Word m_bLaunchedFromDesktop;	///< \ref TRUE if the application was launched by double clicking from a desktop
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
	const char **m_ppOldArgv;		///< Saved pointer to the global __argv for restoring on exit
#endif
public:
	typedef int (BURGER_API *CallbackProc)(ConsoleApp *pThis,const char *pInputFilename,const char *pOutputFilename);	///< Callback for doing the application's work
	typedef void (BURGER_API *UsageProc)(ConsoleApp *pThis); ///< Callback for printing instructions
	ConsoleApp(int iArgc,const char **ppArgv);
	~ConsoleApp();
	BURGER_INLINE void SetArgv(const char **ppArgv) { m_ppArgv=ppArgv; }
	BURGER_INLINE const char ** GetArgv(void) const { return m_ppArgv; }
	BURGER_INLINE void SetArgc(int iArgc) { m_iArgc=iArgc; }
	BURGER_INLINE int GetArgc(void) const { return m_iArgc; }
	BURGER_INLINE Word WasDesktopLaunched(void) const { return m_bLaunchedFromDesktop; }
	void BURGER_API PauseOnError(void) const;
	Word BURGER_API ProcessFilenames(Burger::ConsoleApp::CallbackProc pCallback);
	int BURGER_API InputAndOutput(Burger::ConsoleApp::CallbackProc pCallback,Burger::ConsoleApp::UsageProc pUsage);
	int BURGER_API SimpleTool(Burger::ConsoleApp::CallbackProc pCallback,Burger::ConsoleApp::UsageProc pUsage);
};
}
namespace Burger {
class Compress : public Base {
protected:
	OutputMemoryStream m_Output;		///< Main output buffer for compressed data
	union {
		Word32 u;				///< Access as 32 bit value
		char c[4];				///< Access as a 4 character code
	} m_uSignature;				///< 4 character code to identify this compressor
public:
	enum eError {
		COMPRESS_OKAY,				///< No errors
		COMPRESS_OUTOFMEMORY		///< Error found in compressed data (Decompression was aborted)
	};
	Compress(void);
	virtual ~Compress();
	virtual eError Init(void) = 0;
	virtual eError Process(const void *pInput,WordPtr uInputLength) = 0;
	virtual eError Finalize(void) = 0;
	BURGER_INLINE OutputMemoryStream *GetOutput(void) { return &m_Output; }
	BURGER_INLINE WordPtr GetOutputSize(void) const { return m_Output.GetSize(); }
	BURGER_INLINE Word32 GetSignature(void) const { return m_uSignature.u; }
};
}
namespace Burger {
class CompressILBMRLE : public Compress {
	WordPtr m_uCacheUsed;		///< Number of bytes in the cache
	WordPtr m_uRemaining;		///< Number of bytes unprocessed from the last call to Compact()
	Word8 m_Cache[128+8];		///< Data cache for resuming compression
	eError Compact(const Word8 *pInput,WordPtr uInputLength);
public:
#if defined(BURGER_BIGENDIAN)
	static const Word32 Signature = 0x524C4420;		///< 'RLE '
#else
	static const Word32 Signature = 0x20454C52;		///< 'RLE '
#endif
	CompressILBMRLE(void);
	virtual eError Init(void);
	virtual eError Process(const void *pInput,WordPtr uInputLength);
	virtual eError Finalize(void);
};
}
namespace Burger {
class CompressLZSS : public Compress {
	static const Word RINGBUFFERSIZE=4096;		///< Size of the LZSS ring buffer
	static const Word MAXMATCHLENGTH=18;		///< Largest size of a string to match
	static const Word MINMATCHLENGTH=2;			///< Encode string into position and length
	static const Word NOTUSED=RINGBUFFERSIZE;	///< Index for root of binary search trees
	WordPtr m_uBitMaskOffset;					///< Location in the output stream to store any bit masks
	Word m_uSourceIndex;						///< Index to insert nodes into
	Word m_uDestIndex;							///< Index to remove nodes from (is usually CompressLZSS::m_uSourceIndex-MAXMATCHLENGTH)
	Word m_uCachedLength;						///< Ring buffer cache size (Max CompressLZSS::MAXMATCHLENGTH)
	Word m_uMatchOffset;						///< Offset of string match
	Word m_uMatchSize;							///< Length of string match 0-18 of longest match. These are set by the InsertNode() procedure.
	Word m_uPreviousMatchSize;					///< Length of the last match
	Word m_uMatchIterator;						///< Match size iterator
	Word m_LeftBranch[RINGBUFFERSIZE+1];		///< Left child
	Word m_RightBranch[RINGBUFFERSIZE+1+256];	///< Right child / Hash table
	Word m_RootBranch[RINGBUFFERSIZE+1];		///< Roots for each binary tree left & right children & parents
	Word8 m_bBitMask;							///< Bit field to store in the output stream
	Word8 m_bOrMask;							///< Bit mask for which bit is currently being modified
	Word8 m_RingBuffer[RINGBUFFERSIZE+MAXMATCHLENGTH-1];	///< Ring buffer of size RINGBUFFERSIZE, with extra MAXMATCHLENGTH-1 bytes to facilitate string comparison
	void DeleteNode(WordPtr uNodeNumber);
	void InsertNode(WordPtr uNodeNumber);
	void InitTrees(void);
public:
#if defined(BURGER_BIGENDIAN)
	static const Word32 Signature = 0x4C5A5353;		///< 'LZSS'
#else
	static const Word32 Signature = 0x53535A4C;		///< 'LZSS'
#endif
	CompressLZSS(void);
	virtual eError Init(void);
	virtual eError Process(const void *pInput,WordPtr uInputLength);
	virtual eError Finalize(void);
};
}
namespace Burger {
class CompressDeflate : public Compress {
	enum eState {
		DEFAULT_STATE=0,		///< Dormant state
		INIT_STATE=42,			///< Initialization state
		BUSY_STATE=113,			///< Busy state
		FINISH_STATE=666		///< Finish state
	};
	enum eBlockState {
		STATE_NEEDMORE,      ///< Block not completed, need more input or more output
		STATE_BLOCKDONE,     ///< Block flush performed
		STATE_FINISHSTARTED, ///< Finish started, need only more output at next deflate
		STATE_FINISHDONE     ///< Finish done, accept no more input or output
	};
	enum eDataType {
		Z_BINARY=0,			///< Compress as binary data
		Z_ASCII=1,			///< Compress as ASCII text (Focus on 32-127)
		Z_UNKNOWN=2			///< Unknown data
	};
	enum eStreamTreeType {
		STORED_BLOCK=0,		///< Uncompressed data
		STATIC_TREES=1,		///< Compressed with the static tree
		DYN_TREES=2			///< Compressed with a dynamic tree
	};
	enum {
		MAX_WBITS=15,			///< Number of bits deep a huffman entry can be
		MAX_MEM_LEVEL=9,		///< Memory level
		Z_BEST_COMPRESSION=9,	///< Compression level
		Z_DEFLATED=8,			///< ZLIB token for Deflate
		SMALLEST=1,				///< Index within the heap array of least frequent node in the Huffman tree
		MIN_MATCH=3,			///< Minimum number of bytes of data to compress in a packet
		MAX_MATCH=258,			///< Maximum number of bytes of data to compress in a packet
		DIST_CODE_LEN=512,		///< Length of a distance code
		TOO_FAR=4096,			///< Matches of length 3 are discarded if their distance exceeds TOO_FAR
		MIN_LOOKAHEAD=(MAX_MATCH+MIN_MATCH+1),	///< Minimum amount of lookahead, except at the end of the input file.
		PRESET_DICT=0x20,		///< Preset dictionary flag in zlib header
		LENGTH_CODES=29,		///< Number of length codes, not counting the special END_BLOCK code
		LITERALS=256,			///< Number of literal bytes 0..255
		L_CODES=(LITERALS+1+LENGTH_CODES),	///< Number of Literal or Length codes, including the END_BLOCK code
		D_CODES=30,				///< Number of distance codes
		BL_CODES=19,			///< Number of codes used to transfer the bit lengths
		HEAP_SIZE=(2*L_CODES+1),	///< Maximum heap size
		MAX_BITS=15,			///< All codes must not exceed MAX_BITS bits
		MAX_BL_BITS=7,			///< Bit length codes must not exceed MAX_BL_BITS bits
		END_BLOCK=256,			///< End of block literal code
		REP_3_6=16,				///< Repeat previous bit length 3-6 times (2 bits of repeat count)
		REPZ_3_10=17,			///< Repeat a zero length 3-10 times  (3 bits of repeat count)
		REPZ_11_138=18			///< Repeat a zero length 11-138 times  (7 bits of repeat count)
	};
	struct CodeData_t {
		union {
			Word16 m_uFrequency;	///< Frequency count
			Word16 m_uCode;			///< Bit string
		} m_FrequencyCount;			///< Frequency count/bit string entry
		union {
			Word16 m_uDadBits;		///< Father node in Huffman tree
			Word16 m_uLength;		///< Length of bit string
		} m_DataLength;				///< Data value for the node
	};
	struct StaticTreeDesc_t {
		const CodeData_t *m_pTree;	///< Static tree or \ref NULL
		const int *m_pExtraBits;	///< Extra bits for each code or \ref NULL
		int m_iExtraBase;			///< Base index for extra_bits
		int m_iElements;			///< Max number of elements in the tree
		int m_iMaxLength;			///< Max bit length for the codes
	};
	struct TreeDesc_t {
		CodeData_t *m_pDynamicTree;			///< The dynamic tree
		const StaticTreeDesc_t *m_pStaticTree;	///< The corresponding static tree
		int m_iMaximumCode;					///< Largest code with non zero frequency
	};
	static const Word c_uBufSize = static_cast<Word>(8 * 2*sizeof(Word8));	///< Number of bits used within bi_buf. (bi_buf might be implemented on more than 16 bits on some systems.)
	static const Word c_uWBits = MAX_WBITS;				///< log2(c_uWSize) (8..16)
	static const Word c_uWSize = 1 << c_uWBits;			///< LZ77 window size (32K by default)
	static const Word c_uWMask = c_uWSize - 1;			///< c_uWSize - 1  Use a faster search when the previous match is longer than this
	static const Word c_uHashBits = MAX_MEM_LEVEL + 7;	///< log2(hash_size)
	static const Word c_uHashSize = 1 << c_uHashBits;	///< number of elements in hash table
	static const Word c_uHashMask = c_uHashSize - 1;	///< hash_size-1
	static const Word c_uHashShift = ((c_uHashBits+MIN_MATCH-1)/MIN_MATCH);		///< Number of bits by which m_uInsertHash must be shifted at each input step. It must be such that after MIN_MATCH steps, the oldest byte no longer takes part in the hash key, that is: hash_shift * MIN_MATCH >= hash_bits
	static const Word c_uLiteralBufferSize = 1 << (MAX_MEM_LEVEL + 6);	///< 16K elements by default
	static const Word c_uWindowSize = 2*c_uWSize;		///< Actual size of window: 2*wSize, except when the user input buffer is directly used as sliding window.
	static const Word c_uMaxLazyMatch = 258;	///< Attempt to find a better match only when the current match is strictly smaller than this value. This mechanism is used only for compression levels >= 4.
	static const Word c_uGoodMatch = 32;
	static const int c_iNiceMatch = 258;		///< Stop searching when current match exceeds this
	static const Word c_uMaxChainLength = 4096;	///< To speed up deflation, hash chains are never searched beyond this length.  A higher limit improves compression ratio but degrades the speed.
	const Word8 *m_pInput;		///< Next input byte
	Word8 *m_pPendingOutput;	///< Next pending byte to output to the stream
	WordPtr m_uInputLength;		///< Number of bytes available at next_in
	IntPtr m_iBlockStart;		///< Window position at the beginning of the current output block. Gets negative when the window is moved backwards.
	Word32 m_uAdler;			///< Adler32 value of the uncompressed data
	Word32 m_uOptimalLength;	///< bit length of current block with optimal trees
	Word32 m_uStaticLength;		///< bit length of current block with static trees
	Word m_uInsertHash;			///< hash index of string to be inserted
	Word m_uMatchLength;        ///< Length of best match
	Word m_uPreviousMatch;		///< previous match
	Word m_bMatchAvailable;		///< set if previous match exists
	Word m_uStringStart;		///< start of string to insert
	Word m_uMatchStart;			///< start of matching string
	Word m_uLookAhead;			///< number of valid bytes ahead in window
	Word m_uPreviousLength;		///< Length of the best match at previous step. Matches not greater than this are discarded. This is used in the lazy match evaluation.
	Word m_uLastLiteral;		///< running index in l_buf
	Word m_uMatches;			///< number of string matches in current block
	Word m_uBitIndexBuffer;		///< Number of valid bits in bi_buf.  All bits above the last valid bit are always zero.
	Word m_uBitIndexValid;		///< Number of bits in the output buffer
	Word m_bInitialized;		///< \ref TRUE if initialized
	Word m_uLastEOBLength;		///< bit length of EOB code for last block
	int m_iPending;				///< Number of bytes in the pending buffer
	int m_bNoHeader;			///< Suppress zlib header and adler32
	int m_iLastFlush;			///< Value of flush param for previous deflate call
	int m_iHeapLength;			///< number of elements in the heap
	int m_iHeapMaximum;			///< element of largest frequency
	eState m_eState;			///< As the name implies
	eDataType m_eDataType;		///< UNKNOWN, BINARY or ASCII
	Word8 m_bMethod;			///< STORED (for zip only) or DEFLATED
	CodeData_t m_DynamicLengthTrees[HEAP_SIZE];   ///< literal and length tree
	CodeData_t m_DynamicDistanceTrees[2*D_CODES+1]; ///< distance tree
	CodeData_t m_BitLengthTrees[2*BL_CODES+1];  ///< Huffman tree for bit lengths
	TreeDesc_t m_LiteralDescription;			///<desc. for literal tree
	TreeDesc_t m_DistanceDescription;			///< desc. for distance tree
	TreeDesc_t m_BitLengthDescription;			///< desc. for bit length tree
	int m_Heap[2*L_CODES+1];					///< heap used to build the Huffman trees
	Word16 m_Head[c_uHashSize];					///< Heads of the hash chains or 0.
	Word16 m_Previous[c_uWSize];				///< Link to older string with same hash index. To limit the size of this array to 64K, this link is maintained only for the last 32K strings. An index in this array is thus a window index modulo 32K.
	Word16 m_BitLengthCount[MAX_BITS+1];		///< MAX_BITS = 15, so this is long aligned
	Word16 m_DataBuffer[c_uLiteralBufferSize];		///< Buffer for distances. To simplify the code, d_buf and l_buf have the same number of elements. To use different lengths, an extra flag array would be necessary.
	Word8 m_LiteralBuffer[c_uLiteralBufferSize];	///< buffer for literals or lengths
	Word8 m_PendingBuffer[c_uLiteralBufferSize];	///< Output still pending
	Word8 m_Depth[2*L_CODES+1];					///< Depth of each subtree used as tie breaker for trees of equal frequency
	Word8 m_Window[c_uWSize*2];					///< Sliding window. Input bytes are read into the second half of the window, and move to the first half later to keep a dictionary of at least wSize bytes. With this organization, matches are limited to a distance of wSize-MAX_MATCH bytes, but this ensures that IO is always performed with a length multiple of the block size.
	BURGER_INLINE Word TallyLiteral(Word uInput)
	{
		Word uLastLiteral = m_uLastLiteral;
		m_DataBuffer[uLastLiteral] = 0;
		m_LiteralBuffer[uLastLiteral] = static_cast<Word8>(uInput);
		++uLastLiteral;
		++m_DynamicLengthTrees[uInput].m_FrequencyCount.m_uFrequency;
		m_uLastLiteral = uLastLiteral;
		return (uLastLiteral == (c_uLiteralBufferSize-1));
	}
	BURGER_INLINE Word TallyDistance(Word uDistance,Word uLength)
	{
		Word uLastLiteral = m_uLastLiteral;
		m_DataBuffer[uLastLiteral] = static_cast<Word16>(uDistance);
		m_LiteralBuffer[uLastLiteral] = static_cast<Word8>(uLength);
		++uLastLiteral;
		--uDistance;
		m_DynamicLengthTrees[g_LengthCodes[uLength]+LITERALS+1].m_FrequencyCount.m_uFrequency++;
		m_DynamicDistanceTrees[(uDistance < 256) ? g_DistanceCodes[uDistance] : g_DistanceCodes[256+(uDistance>>7)]].m_FrequencyCount.m_uFrequency++;
		m_uLastLiteral = uLastLiteral;
		return (uLastLiteral == (c_uLiteralBufferSize-1));
	}
/* ===========================================================================
 * Send a value on a given number of bits.
 * IN assertion: length <= 16 and value fits in length bits.
 */
	BURGER_INLINE void SendBits(Word uInput,Word uLength)
	{
		Word uBits = m_uBitIndexBuffer | (uInput<<m_uBitIndexValid);
		if (static_cast<int>(m_uBitIndexValid) > static_cast<int>(c_uBufSize - uLength)) {
			Word uPending = static_cast<Word>(m_iPending);
			Word8 *pOutput = &m_PendingBuffer[uPending];
			m_iPending = static_cast<int>(uPending+2);
			pOutput[0] = static_cast<Word8>(uBits & 0xff);
			pOutput[1] = static_cast<Word8>(uBits >> 8);
			uBits = static_cast<Word>(static_cast<Word16>(uInput) >> (c_uBufSize - m_uBitIndexValid));
			uLength -= c_uBufSize;
		}
		m_uBitIndexBuffer = uBits;
		m_uBitIndexValid += uLength;
	}
	BURGER_INLINE void send_code(Word uCode,const CodeData_t *pTree)
	{
		SendBits(pTree[uCode].m_FrequencyCount.m_uCode,pTree[uCode].m_DataLength.m_uLength);
	}
/* ===========================================================================
 * Initialize the hash table (avoiding 64K overflow for 16 bit systems).
 * prev[] will be initialized on the fly.
 */
	BURGER_INLINE void ClearHash(void)
	{
		MemoryClear(m_Head,sizeof(m_Head));
	}
/* ===========================================================================
 * Update a hash value with the given input byte
 * IN  assertion: all calls to to UPDATE_HASH are made with consecutive
 *    input characters, so that a running hash key can be computed from the
 *    previous key instead of complete recalculation each time.
 */
	BURGER_INLINE static Word UpdateHash(Word uHash,Word8 uInput)
	{
		return ((uHash<<c_uHashShift) ^ uInput) & c_uHashMask;
	}
/* ===========================================================================
 * Insert string str in the dictionary and set match_head to the previous head
 * of the hash chain (the most recent string with same hash key). Return
 * the previous length of the hash chain.
 * If this file is compiled with -DFASTEST, the compression level is forced
 * to 1, and no hash chains are maintained.
 * IN  assertion: all calls to to INSERT_STRING are made with consecutive
 *    input characters and the first MIN_MATCH bytes of str are valid
 *    (except for the last MIN_MATCH-1 bytes of the input file).
 */
	BURGER_INLINE Word InsertString(Word uStringIndex)
	{
		m_uInsertHash = UpdateHash(m_uInsertHash,m_Window[uStringIndex + (MIN_MATCH-1)]);
		Word uMatchHead = m_Head[m_uInsertHash];
		m_Previous[uStringIndex & c_uWMask] = static_cast<Word16>(uMatchHead);
		m_Head[m_uInsertHash] = static_cast<Word16>(uStringIndex);
		return uMatchHead;
	}
/* ===========================================================================
 * Flush the current block, with given end-of-file flag.
 * IN assertion: strstart is set to the end of the current match.
 */
	BURGER_INLINE void FlushBlock(Word bEOF)
	{
		FlushBlock((m_iBlockStart >= 0) ? &m_Window[static_cast<Word>(m_iBlockStart)] : NULL,static_cast<Word32>(m_uStringStart - m_iBlockStart),bEOF);
		m_iBlockStart = static_cast<IntPtr>(m_uStringStart);
		FlushPending();
	}
	void OutputBigEndian16(Word b);
	void BitIndexFlush(void);
	void BitIndexFlushToByte(void);
	void CopyBlock(const Word8 *pInput,WordPtr uInputLength);
	void SetDataType(void);
	void InitBlock(void);
	void StaticTreeInit(void);
	void PQDownHeap(const CodeData_t *pTree,int k);
	void CompressBlock(const CodeData_t *pLengthTree,const CodeData_t *pDistanceTree);
	WordPtr ReadBuffer(Word8 *pOutput,WordPtr uOutputSize);
	void FillWindow(void);
	void GenerateBitLengths(const TreeDesc_t *pTreeDescription);
	void GenerateCodes(CodeData_t *tree, int max_code, Word16 *bl_count);
	void BuildTree(TreeDesc_t *desc);
	void ScanTree(CodeData_t *tree,int max_code);
	int BuildBitLengthTree(void);
	void StoredBlock(const Word8 *buf,Word32 stored_len,int eof);
	void SendTree(CodeData_t *tree, int max_code);
	void SendAllTrees(int lcodes,int dcodes,int blcodes);
	void FlushBlock(const Word8 *buf,Word32 stored_len,Word bEOF);
	void FlushPending(void);
	Word LongestMatch(Word cur_match);
	eBlockState DeflateSlow(int flush);
	void Align(void);
	int DeflateEnd(void);
	void LongestMatchInit(void);
	int DeflateReset(void);
	int DeflateInit(void);
	int PerformDeflate(int flush);
	static const int g_ExtraLengthBits[LENGTH_CODES];
	static const int g_ExtraDistanceBits[D_CODES];
	static const int g_ExtraBitLengthBits[BL_CODES];
	static const Word8 g_BitLengthOrder[BL_CODES];
	static const CodeData_t g_StaticLengthTrees[L_CODES+2];
	static const CodeData_t g_StaticDistanceTrees[D_CODES];
	static const int g_BaseLengths[LENGTH_CODES];
	static const int g_BaseDistances[D_CODES];
	static const StaticTreeDesc_t g_StaticLengthDescription;
	static const StaticTreeDesc_t g_StaticDistanceDescription;
	static const StaticTreeDesc_t g_StaticBitLengthDescription;
	static const Word8 g_DistanceCodes[DIST_CODE_LEN];
	static const Word8 g_LengthCodes[MAX_MATCH-MIN_MATCH+1];
public:
#if defined(BURGER_BIGENDIAN)
	static const Word32 Signature = 0x5A4C4942;		///< 'ZLIB'
#else
	static const Word32 Signature = 0x42494C5A;		///< 'ZLIB'
#endif
	CompressDeflate(void);
	virtual eError Init(void);
	virtual eError Process(const void *pInput,WordPtr uInputLength);
	virtual eError Finalize(void);
};
}
namespace Burger {
class Decompress : public Base {
protected:
	WordPtr m_uTotalInput;		///< Total number of bytes processed for input
	WordPtr m_uTotalOutput;		///< Total number of bytes processed for output
	WordPtr m_uInputLength;		///< Number of input bytes processed from the last call to Process()
	WordPtr m_uOutputLength;	///< Number of output bytes processed from the last call to Process()
	char m_uSignature[4];		///< 4 character code to identify this decompressor
public:
	enum eError {
		DECOMPRESS_OKAY,		///< No errors
		DECOMPRESS_OUTPUTUNDERRUN,	///< All input was exhausted before output was satisfied
		DECOMPRESS_OUTPUTOVERRUN,	///< Input data remained after output was satisfied
		DECOMPRESS_BADINPUT			///< Error found in compressed data (Decompression was aborted)
	};
	Decompress(void);
	virtual eError Reset(void) = 0;
	virtual eError Process(void *pOutput,WordPtr uOutputChunkSize,const void *pInput,WordPtr uInputChunkLength) = 0;
	BURGER_INLINE WordPtr GetTotalInputSize(void) const { return m_uTotalInput; }
	BURGER_INLINE WordPtr GetTotalOutputSize(void) const { return m_uTotalOutput; }
	BURGER_INLINE WordPtr GetProcessedInputSize(void) const { return m_uInputLength; }
	BURGER_INLINE WordPtr GetProcessedOutputSize(void) const { return m_uOutputLength; }
	BURGER_INLINE Word32 GetSignature(void) const { return reinterpret_cast<const Word32 *>(m_uSignature)[0]; }
};
}
namespace Burger {
class DecompressILBMRLE : public Decompress {
	enum eState {
		STATE_INIT,			///< Start of a compression token
		STATE_FILLTOKEN,	///< Obtained a fill token, awaiting fill byte
		STATE_FILL,			///< Data fill in progress
		STATE_RUN			///< Raw data copy in progress
	};
	WordPtr m_uRun;		///< Run in progress
	Word m_uFill;		///< Last fill value
	eState m_eState;	///< State of the decompression
public:
#if defined(BURGER_BIGENDIAN)
	static const Word32 Signature = 0x524C4420;		///< 'RLE '
#else
	static const Word32 Signature = 0x20454C52;		///< 'RLE '
#endif
	DecompressILBMRLE();
	virtual eError Reset(void);
	virtual eError Process(void *pOutput,WordPtr uOutputChunkLength,const void *pInput,WordPtr uInputChunkLength);
};
extern Decompress::eError BURGER_API SimpleDecompressILBMRLE(void *pOutput,WordPtr uOutputChunkLength,const void *pInput,WordPtr uInputChunkLength);
}
namespace Burger {
class DecompressLZSS : public Decompress {
	enum eState {
		STATE_INIT,			///< Start of a compression token
		STATE_16BIT2,		///< Grab the 2nd half of a 16 bit run token
		STATE_RUN			///< Memory copy in progress
	};
	WordPtr m_uRunCount;	///< Previous 16 bit token (Half)
	WordPtr m_uOffset;		///< Previous destination pointer
	Word m_uBitBucket;		///< Previous bit bucket
	eState m_eState;		///< State of the decompression
public:
#if defined(BURGER_BIGENDIAN)
	static const Word32 Signature = 0x4C5A5353;		///< 'LZSS'
#else
	static const Word32 Signature = 0x53535A4C;		///< 'LZSS'
#endif
	DecompressLZSS();
	virtual eError Reset(void);
	virtual eError Process(void *pOutput,WordPtr uOutputChunkLength,const void *pInput,WordPtr uInputChunkLength);
};
extern Decompress::eError BURGER_API SimpleDecompressLZSS(void *pOutput,WordPtr uOutputChunkLength,const void *pInput,WordPtr uInputChunkLength);
}
namespace Burger {
class DecompressDeflate : public Decompress {
	enum eState {
		STATE_METHOD,	///< Waiting for method byte
		STATE_FLAG,		///< Waiting for flag byte
		STATE_DICT4,	///< Four dictionary check bytes to go
		STATE_DICT3,	///< Three dictionary check bytes to go
		STATE_DICT2,	///< Two dictionary check bytes to go
		STATE_DICT1,	///< One dictionary check byte to go
		STATE_DICT0,	///< Waiting for inflateSetDictionary
		STATE_BLOCKS,	///< Decompressing blocks
		STATE_CHECK4,	///< Four check bytes to go
		STATE_CHECK3,	///< Three check bytes to go
		STATE_CHECK2,	///< Two check bytes to go
		STATE_CHECK1,	///< One check byte to go
		STATE_COMPLETE,	///< Decompression completed
		STATE_ABORT		///< Decompression aborted (Fatal)
	};
	enum eBlockMode {
		BLOCKMODE_TYPE,			///< Get type bits (3, including end bit)
		BLOCKMODE_LENS,			///< Get lengths for stored
		BLOCKMODE_STORED,		///< Processing stored block
		BLOCKMODE_TABLE,		///< Get table lengths
		BLOCKMODE_BTREE,		///< Get bit lengths tree for a dynamic block
		BLOCKMODE_DTREE,		///< Get length, distance trees for a dynamic block
		BLOCKMODE_CODES,		///< Processing fixed or dynamic block
		BLOCKMODE_DRY,			///< Output remaining window bytes
		BLOCKMODE_COMPLETED,	///< Block completed
		BLOCKMODE_ABORT			///< Block aborted (Fatal)
	};
	enum eCodesMode {
		CODES_START,	///< Set up for CODES_LEN
		CODES_LEN,		///< Input / Get length/literal/eob next
		CODES_LENEXT,	///< Input / Getting length extra (have base)
		CODES_DIST,		///< Input / Get distance next
		CODES_DISTEXT,	///< Input / Getting distance extra
		CODES_COPY,		///< Output / Copying bytes in window, waiting for space
		CODES_LITERAL,	///< Output / Got literal, waiting for output space
		CODES_WASH,		///< Output / Got end of byte, possibly still output waiting
		CODES_END,		///< Got end of byte and all data flushed
		CODES_ABORT		///< Aborted due to error
	};
	enum {
		FIXED_BLOCKLENGTH=9,		///< Length in 2^?? bits
		FIXED_BLOCKDISTANCE=5,		///< Distance in 2^?? bits
		MAX_WBITS=15,				///< Maximum bits for the depth of the huffman tree
		MAXTREEDYNAMICSIZE=1440,	///< Maximum size of the dynamic tree
		PRESET_DICT=0x20,			///< Preset dictionary flag in zlib header
		Z_DEFLATED=8				///< ZLib flag for deflation decompression
	};
	struct DeflateHuft_t {
		Word8 m_bExtraOperation;	///< Number of extra bits or operation
		Word8 m_bBitCount;			///< Number of bits in this code or subcode
		Word16 m_uBase;				///< Literal, length base, distance base, or table offset
	};
	const Word8 *m_pInput;		///< Packed data pointer
	Word8 *m_pOutput;			///< Output data pointer
	const Word8 *m_pWindowRead;	///< Window read pointer
	Word8 *m_pWindowWrite;		///< Window write pointer
	const DeflateHuft_t *m_pCodeTree;	///< Pointer into tree
	const DeflateHuft_t *m_pCodeTreeLength;	///< Pointer to literal/length/eob tree
	const DeflateHuft_t *m_pCodeTreeDistance;	///< Pointer distance tree
	Word *m_pTreesLengths;			///< Pointer to bit lengths of codes
	DeflateHuft_t *m_pTreesHuffman;	///< Pointer to bit length decoding tree
	WordPtr m_uInputChunkLength;	///< Number of packed bytes remaining
	WordPtr m_uOutputChunkLength;	///< Number of bytes in the output buffer
	WordPtr m_uStoredBytesToCopy;	///< If STORED, bytes left to copy
	eState m_eState;			///< State of the decompression
	eBlockMode m_eBlockMode;	///< Current decompression block mode
	eCodesMode m_eCodesMode;	///< Current inflate_codes mode
	Word32 m_uChecksumOfChunk;	///< Computed checksum value of decompressed data
	Word32 m_uChecksumInStream;	///< 32 bit literal pulled from the big endian data stream (Must match DecompressDeflate::m_uChecksumInStream)
	Word32 m_uAlder32Checksum;	///< Checksum on output
	Word32 m_uBitBucket;		///< Bit buffer
	Word m_uCompressionMethod;	///< Compression method type
	Word m_bLastBlock;			///< TRUE if this block is the last block
	Word m_uBitCount;			///< Bits in bit buffer
	Word m_uCodeLength;			///< Length in bits of the last code
	Word m_uCodeTreeNeed;		///< Bits needed
	Word m_uCodeLiteral;		///< Literal code fetched
	Word m_uCodeCopyGet;		///< Bits to get for extra token
	Word m_uCodeCopyDistance;	///< Distance back to copy from
	Word m_uTreesTable;			///< Table lengths (14 bits)
	Word m_uTreesIndex;			///< Index into blends (or border)
	Word m_uTreesDepth;			///< Bit length tree depth
	Word8 m_bCodeLengthBits;	///< Length tree bits decoded per branch
	Word8 m_bCodeDistanceBits;	///< Distance tree bits decoder per branch
	Word8 m_WindowBuffer[1<<MAX_WBITS];	///< Sliding window
	DeflateHuft_t m_HuffmanTable[MAXTREEDYNAMICSIZE];	///< Single data chunk for tree space
	static const DeflateHuft_t s_FixedTreeLiteral[];
	static const DeflateHuft_t s_FixedTreeDistance[];
	int Flush(int iErrorCode);
	int Fast(Word uBitLength,Word uBitDistance,const DeflateHuft_t *pHuffmanLength,const DeflateHuft_t *pHuffmanDistance);
	int ProcessCodes(int iErrorCode);
	void CodesReset(Word bCodeLengthBits,Word bCodeDistanceBits,const DeflateHuft_t *pCodeTreeLength,const DeflateHuft_t *pCodeTreeDistance);
	static int BuildHuffmanTrees(const Word *pSampleCounts,Word uNumberSamples,Word uMaxSample,const Word *pDefaultLengths,const Word *pDefaultBits,DeflateHuft_t **ppNewTree,Word *pNewTreeSize,DeflateHuft_t *pExistingTree,Word *pHuffmanCount,Word *pWorkArea);
	static int TreesBits(const Word *pSampleCounts,Word *pNewTreeSize,DeflateHuft_t **ppNewTree,DeflateHuft_t *pExistingTree);
	static int TreesDynamic(Word uNumberSamples,Word uNumberDistance,const Word *pSampleCounts,Word *pNewTreeSize,Word *pNewDistanceSize,DeflateHuft_t **ppNewTree,DeflateHuft_t **ppNewDistance,DeflateHuft_t *pExistingTree);
	void BlocksReset(void);
	int ProcessBlocks(int iErrorCode);
public:
#if defined(BURGER_BIGENDIAN)
	static const Word32 Signature = 0x5A4C4942;		///< 'ZLIB'
#else
	static const Word32 Signature = 0x42494C5A;		///< 'ZLIB'
#endif
	DecompressDeflate();
	~DecompressDeflate();
	virtual eError Reset(void);
	virtual eError Process(void *pOutput,WordPtr uOutputChunkLength,const void *pInput,WordPtr uInputChunkLength);
};
extern Decompress::eError BURGER_API SimpleDecompressDeflate(void *pOutput,WordPtr uOutputChunkLength,const void *pInput,WordPtr uInputChunkLength);
}
namespace Burger {
class RezFile {
	BURGER_DISABLECOPYCONSTRUCTORS(RezFile);
public:
	static const char g_RezFileSignature[4];		///< 'BRGR'
	enum {
		MAXCODECS=3,			///< Maximum number of compression codecs available
		ROOTHEADERSIZE = static_cast<int>(sizeof(Word32)*2)+(MAXCODECS*4)+4,	///< Size of RootHeader_t on disk
		ENTRYFLAGSNAMEOFFSETMASK=0x0007FFFF,	///< Filename offset
		ENTRYFLAGSDECOMPMASK=0x00180000,	///< Mask for decompressors (2 bits)
		ENTRYFLAGSHIGHMEMORY=0x00200000,	///< True if load in fixed memory
		ENTRYFLAGSREFCOUNT=0xFF000000,	///< Refcount mask
		ENTRYFLAGSREFSHIFT=24,				///< Bits to shift for the refcount
		ENTRYFLAGSREFADD=(1<<ENTRYFLAGSREFSHIFT),	///< 1 in refcount format
		ENTRYFLAGSDECOMPSHIFT=19			///< Shift value to get the decompression type index (2 bits)
	};
	static const Word INVALIDREZNUM = static_cast<Word>(-1);	///< Illegal resource number, used as an error code
	struct RootHeader_t {
		char m_Name[4];			///< 'BRGR'
		Word32 m_uGroupCount;	///< Number of entries
		Word32 m_uMemSize;		///< Amount of memory the entries take up
		char m_CodecID[MAXCODECS][4];	///< Compression codecs used
	};
	struct FileRezEntry_t {
		Word32 m_uFileOffset;	///< Place in the rez file for the data
		Word32 m_uLength;		///< Size of the data in the rez file (Uncompressed)
		Word32 m_uNameOffset;	///< Offset to the filename
		Word32 m_uCompressedLength;	///< Size of the data COMPRESSED, in the rez file, with the upper 3 bits as flags
	};
	struct FileRezGroup_t {
		Word32 m_uBaseRezNum;	///< Resource base ID
		Word32 m_uCount;		///< Number of resources in the group
		FileRezEntry_t m_Array[1];	///< Array of resources
	};
private:
	enum {
		MAXBUFFER = 65536,					///< Size of decompression buffer
		REZOFFSETFIXED=0x80000000,			///< True if load in fixed memory
		REZOFFSETDECOMPMASK=0x60000000,		///< Mask for decompressors
		REZOFFSETMASK=0x1FFFFFFF,			///< Big enough for 1 Gig file (GD-ROM or CDRom)
		REZOFFSETDECOMPSHIFT=29,			///< Decompressor mask shift value (Matches REZOFFSETDECOMPMASK)
		ENTRYFLAGSTESTED=0x00000001,		///< True if the filename was checked
		ENTRYFLAGSFILEFOUND=0x0000002,		///< True if a file was found
		SWAPENDIAN=0x01,					///< Manually swap endian
		OLDFORMAT=0x02						///< Parsing an old rez file format
	};
	struct RezEntry_t {
		void **m_ppData;		///< Handle to data in memory
		const char *m_pRezName;	///< Pointer to the resource name, or \ref NULL if none
		Word32 m_uFileOffset;	///< Offset into the rez file
		Word32 m_uLength;		///< Length of the data when decompressed in memory
		Word32 m_uFlags;		///< Offset to the filename, Flags and Refcount
		Word32 m_uCompressedLength;	///< Length of the data compressed
	};
	struct RezGroup_t {
		Word m_uBaseRezNum;		///< Base Resource number
		Word m_uCount;			///< Number of entries
		RezEntry_t m_Array[1];	///< First entry
	};
public:
	struct FilenameToRezNum_t {
		const char *m_pRezName;	///< Pointer to the filename
		Word m_uRezNum;			///< Resource number associated with this entry
	};
private:
	Burger::Decompress *m_Decompressors[MAXCODECS];	///< Decompressor functions
	Burger::File m_File;				///< Open file reference
	Burger::MemoryManagerHandle *m_pMemoryManager;	///< Pointer to the handle based memory manager to use
	Word32 m_uGroupCount;				///< Number of resource groups
	Word32 m_uRezNameCount;				///< Number of resource names in m_pRezNames
	RezGroup_t *m_pGroups;				///< Array of resource groups
	FilenameToRezNum_t *m_pRezNames;	///< Pointer to sorted resource names if present
	Word m_bExternalFileEnabled;		///< \ref TRUE if external file access is enabled
	static int BURGER_ANSIAPI QSortNames(const void *pFirst,const void *pSecond);
	WordPtr BURGER_API GetRezGroupBytes(void) const;
	void BURGER_API AdjustNamePointers(WordPtr uAdjust);
	RezEntry_t * BURGER_API Find(Word uRezNum) const;
	Word BURGER_API FindName(const char *pRezName,FilenameToRezNum_t **ppOutput) const;
	static RezGroup_t * BURGER_API ParseRezFileHeader(const Word8 *pData,const RootHeader_t *pHeader,Word uSwapFlag,Word32 uStartOffset);
	void BURGER_API ProcessRezNames(void);
	void BURGER_API FixupFilenames(char *pText);
public:
	RezFile(Burger::MemoryManagerHandle *pMemoryManager);
	~RezFile();
	static RezFile * BURGER_API New(Burger::MemoryManagerHandle *pMemoryManager,const char *pFileName,Word32 uStartOffset=0);
	Word BURGER_API Init(const char *pFileName,Word32 uStartOffset=0);
	void BURGER_API Shutdown(void);
	void BURGER_API PurgeCache(void);
	Word BURGER_API SetExternalFlag(Word bEnable);
	Word BURGER_INLINE GetExternalFlag(void) const { return m_bExternalFileEnabled; }
	void BURGER_API LogDecompressor(Word uCompressID,Burger::Decompress *pProc);
	Word BURGER_API GetRezNum(const char *pRezName) const;
	Word BURGER_API GetName(Word uRezNum,char *pBuffer,WordPtr uBufferSize) const;
	Word BURGER_API AddName(const char *pRezName);
	void BURGER_API Remove(Word uRezNum);
	void BURGER_API Remove(const char *pRezName);
	BURGER_INLINE const FilenameToRezNum_t * GetNameArray(void) const { return m_pRezNames; }
	BURGER_INLINE Word GetNameArraySize(void) const { return m_uRezNameCount; }
	Word BURGER_API GetLowestRezNum(void) const;
	Word BURGER_API GetHighestRezNum(void) const;
	WordPtr BURGER_API GetSize(Word uRezNum) const;
	WordPtr BURGER_API GetCompressedSize(Word uRezNum) const;
	Word BURGER_API GetIDFromHandle(const void **ppRez,Word *pRezNum,char *pBuffer,WordPtr uBufferSize) const;
	Word BURGER_API GetIDFromPointer(const void *pRez,Word *pRezNum,char *pBuffer,WordPtr uBufferSize) const;
	void ** BURGER_API LoadHandle(Word uRezNum,Word *pLoadedFlag=NULL);
	void ** BURGER_API LoadHandle(const char *pRezName,Word *pLoadedFlag=NULL);
	void * BURGER_API Load(Word uRezNum,Word *pLoadedFlag=NULL);
	void * BURGER_API Load(const char *pRezName,Word *pLoadedFlag=NULL);
	Word BURGER_API Read(Word uRezNum,void *pBuffer,WordPtr uBufferSize);
	Word BURGER_API Read(const char *pRezName,void *pBuffer,WordPtr uBufferSize);
	void BURGER_API Release(Word uRezNum);
	void BURGER_API Release(const char *pRezName);
	void BURGER_API Kill(Word uRezNum);
	void BURGER_API Kill(const char *pRezName);
	void BURGER_API Detach(Word uRezNum);
	void BURGER_API Detach(const char *pRezName);
	void BURGER_API Preload(Word uRezNum);
	void BURGER_API Preload(const char *pRezName);
};
}
namespace Burger {
class Keyboard;
class Joypad;
class Mouse;
class Sound;
class Display;
class Renderer;
class GameApp : public Burger::Base {
	BURGER_DISABLECOPYCONSTRUCTORS(GameApp);
protected:
	Keyboard *m_pKeyboard;			///< Pointer to the active keyboard instance
	Mouse *m_pMouse;				///< Pointer to the active mouse instance
	Joypad *m_pJoypad;				///< Pointer to the active joypad instance
	Sound *m_pSound;				///< Pointer to the active sound instance
	Display *m_pDisplay;			///< Pointer to the active display instance
	Renderer *m_pRenderer;			///< Pointer to the active display renderer
	const char **m_ppArgv;			///< Arguments passed to the console
	MemoryManagerGlobalHandle m_MemoryManagerHandle;	///< Handle based memory manager for the app
	RunQueue m_RunQueue;			///< Internal run queue
	int m_iArgc;					///< Number of valid arguments
	Word m_bQuit;					///< Set to \ref TRUE when the application has to shut down
	Word m_bInBackground;			///< Set to \ref TRUE if the game should be paused due to another window being in front
	Word m_bMinimized;				///< Set to \ref TRUE if the game is minimized (PC/Mac only, always false on consoles)
	Word m_bAllowWindowSwitching;	///< Set to \ref TRUE if the game allows switching to windowed mode via Alt-Enter on desktop/laptops
	Word m_bMouseOnScreen;			///< \ref TRUE if the mouse cursor is on the screen in windows systems
	Word m_bWindowSwitchRequested;	///< \ref TRUE if the window resolution switch key was pressed
public:
	GameApp(WordPtr uDefaultMemorySize=Burger::MemoryManagerHandle::DEFAULTMEMORYCHUNK,Word uDefaultHandleCount=Burger::MemoryManagerHandle::DEFAULTHANDLECOUNT,WordPtr uMinReserveSize=Burger::MemoryManagerHandle::DEFAULTMINIMUMRESERVE);
	~GameApp();
	BURGER_INLINE void Poll(void) { m_RunQueue.Call(); };
	BURGER_INLINE void AddRoutine(RunQueue::CallbackProc Proc,void *pData) { m_RunQueue.Add(Proc,pData); }
	BURGER_INLINE void RemoveRoutine(RunQueue::CallbackProc Proc,void *pData) { m_RunQueue.Remove(Proc,pData); }
	BURGER_INLINE RunQueue *GetRunQueue(void) { return &m_RunQueue; }
	BURGER_INLINE MemoryManagerGlobalHandle * GetMemoryManager(void) { return &m_MemoryManagerHandle; }
	BURGER_INLINE void SetArgv(const char **ppArgv) { m_ppArgv=ppArgv; }
	BURGER_INLINE const char ** GetArgv(void) const { return m_ppArgv; }
	BURGER_INLINE void SetArgc(int iArgc) { m_iArgc=iArgc; }
	BURGER_INLINE int GetArgc(void) const { return m_iArgc; }
	BURGER_INLINE void SetQuitCode(void) { m_bQuit = TRUE; }
	BURGER_INLINE void ClearQuitCode(void) { m_bQuit = FALSE; }
	BURGER_INLINE Word GetQuitCode(void) const { return m_bQuit; }
	BURGER_INLINE void SetInBackground(Word bInBackground) { m_bInBackground = bInBackground; }
	BURGER_INLINE Word IsInBackground(void) const { return m_bInBackground; }
	BURGER_INLINE void SetKeyboard(Keyboard *pKeyboard) { m_pKeyboard = pKeyboard; }
	BURGER_INLINE Keyboard *GetKeyboard(void) const { return m_pKeyboard; }
	BURGER_INLINE void SetMouse(Mouse *pMouse) { m_pMouse = pMouse; }
	BURGER_INLINE Mouse *GetMouse(void) const { return m_pMouse; }
	BURGER_INLINE void SetJoypad(Joypad *pJoypad) { m_pJoypad = pJoypad; }
	BURGER_INLINE Joypad *GetJoypad(void) const { return m_pJoypad; }
	BURGER_INLINE void SetSound(Sound *pSound) { m_pSound = pSound; }
	BURGER_INLINE Sound *GetSound(void) const { return m_pSound; }
	BURGER_INLINE void SetDisplay(Display *pDisplay) { m_pDisplay = pDisplay; }
	BURGER_INLINE Display *GetDisplay(void) const { return m_pDisplay; }
	BURGER_INLINE void SetRenderer(Renderer *pRenderer) { m_pRenderer = pRenderer; }
	BURGER_INLINE Renderer *GetRenderer(void) const { return m_pRenderer; }
	BURGER_INLINE void SetWindowSwitching(Word bAllowWindowSwitching) { m_bAllowWindowSwitching = bAllowWindowSwitching; }
	BURGER_INLINE Word IsWindowSwitchingAllowed(void) const { return m_bAllowWindowSwitching; }
	Word BURGER_API SwitchVideo(void);
	BURGER_INLINE Word IsMinimized(void) const { return m_bMinimized; }
	BURGER_INLINE void SetMinimized(Word bMinimized) { m_bMinimized = bMinimized; }
	Word BURGER_API IsAppFullScreen(void) const;
	Word BURGER_API IsResizingAllowed(void) const;
	BURGER_INLINE void SetMouseOnScreen(Word bMouseOnScreen) { m_bMouseOnScreen = bMouseOnScreen; }
	BURGER_INLINE Word IsMouseOnScreen(void) const { return m_bMouseOnScreen; }
	BURGER_INLINE void SetWindowSwitchRequested(Word bWindowSwitchRequested) { m_bWindowSwitchRequested = bWindowSwitchRequested; }
	BURGER_INLINE Word IsWindowSwitchRequested(void) const { return m_bWindowSwitchRequested; }
};
}
extern int BURGER_API CodeEntry(Burger::GameApp *pGameApp);
namespace Burger {
class Renderer {
public:
	static const Word ByteSquareTable[255+256];					///< Table of squares from -255 to 255
	static const Word8 BURGER_ALIGN(RGB2ToRGB3Table[4],4);		///< Table to convert 2 bit color to 3 bit color
	static const Word8 BURGER_ALIGN(RGB2ToRGB4Table[4],4);		///< Table to convert 2 bit color to 4 bit color
	static const Word8 BURGER_ALIGN(RGB2ToRGB5Table[4],4);		///< Table to convert 2 bit color to 5 bit color
	static const Word8 BURGER_ALIGN(RGB2ToRGB6Table[4],4);		///< Table to convert 2 bit color to 6 bit color
	static const Word8 BURGER_ALIGN(RGB2ToRGB8Table[4],4);		///< Table to convert 2 bit color to 8 bit color
	static const Word8 BURGER_ALIGN(RGB3ToRGB4Table[8],8);		///< Table to convert 3 bit color to 4 bit color
	static const Word8 BURGER_ALIGN(RGB3ToRGB5Table[8],8);		///< Table to convert 3 bit color to 5 bit color
	static const Word8 BURGER_ALIGN(RGB3ToRGB6Table[8],8);		///< Table to convert 3 bit color to 6 bit color
	static const Word8 BURGER_ALIGN(RGB3ToRGB8Table[8],8);		///< Table to convert 3 bit color to 8 bit color
	static const Word8 BURGER_ALIGN(RGB4ToRGB5Table[16],16);	///< Table to convert 4 bit color to 5 bit color
	static const Word8 BURGER_ALIGN(RGB4ToRGB6Table[16],16);	///< Table to convert 4 bit color to 6 bit color
	static const Word8 BURGER_ALIGN(RGB4ToRGB8Table[16],16);	///< Table to convert 4 bit color to 8 bit color
	static const Word8 BURGER_ALIGN(RGB5ToRGB6Table[32],16);	///< Table to convert 5 bit color to 6 bit color
	static const Word8 BURGER_ALIGN(RGB5ToRGB8Table[32],16);	///< Table to convert 5 bit color to 8 bit color
	static const Word8 BURGER_ALIGN(RGB6ToRGB8Table[64],16);	///< Table to convert 6 bit color to 8 bit color
	Renderer(void);
	virtual ~Renderer();
	virtual Word Init(Word uWidth,Word uHeight,Word uDepth,Word uFlags);
	virtual void Shutdown(void);
	virtual void BeginScene(void);
	virtual void EndScene(void);
	virtual void Draw8BitPixels(int iX,int iY,Word uWidth,Word uHeight,WordPtr uStride,const Word8 *pPixels);
	virtual void Draw8BitPixelsMasked(int iX,int iY,Word uWidth,Word uHeight,WordPtr uStride,const Word8 *pPixels);
	virtual void DrawPixel(int iX,int iY,Word uColorIndex);
	virtual void DrawRect(int iX,int iY,Word uWidth,Word uHeight,Word uColorIndex);
	virtual void Clear(Word uColorIndex);
protected:
	virtual void UpdateClip(void);
	Rect_t m_Clip;			///< Bounds rectangle for clipping
	Display *m_pDisplay;	///< Attached display
	void *m_pFrameBuffer;	///< Pointer to the software frame buffer (If supported)
	WordPtr m_uStride;		///< Width in BYTES of the display buffer (For software rendering)
	Word m_uWidth;			///< Width in pixels of the display buffer
	Word m_uHeight;			///< Height in pixels of the display buffer
	Word m_uDepth;			///< Depth in bits of the display buffer
	Word m_uFlags;			///< Flags for describing available features
public:
	BURGER_INLINE Display *GetDisplay(void) const { return m_pDisplay; }
	BURGER_INLINE void SetDisplay(Display *pDisplay) { m_pDisplay = pDisplay; }
	BURGER_INLINE void *GetFrameBuffer(void) const { return m_pFrameBuffer; }
	BURGER_INLINE void SetFrameBuffer(void *pFrameBuffer) { m_pFrameBuffer = pFrameBuffer; }
	BURGER_INLINE WordPtr GetStride(void) const { return m_uStride; }
	BURGER_INLINE void SetStride(WordPtr uStride) { m_uStride = uStride; }
	BURGER_INLINE Word GetWidth(void) const { return m_uWidth; }
	BURGER_INLINE Word GetHeight(void) const { return m_uHeight; }
	BURGER_INLINE Word GetDepth(void) const { return m_uDepth; }
	BURGER_INLINE Word GetFlags(void) const { return m_uFlags; }
	BURGER_INLINE const Rect_t *GetClip(void) const { return &m_Clip; }
	void GetClip(Rect_t *pOutput) const;
	void SetClip(const Rect_t *pInput);
	void SetClip(int iLeft,int iTop,int iRight,int iBottom);
	void DrawShape8Bit(int iX,int iY,RezFile *pRezFile,Word uRezNum);
	void DrawShape8BitCentered(RezFile *pRezFile,Word uRezNum);
	void DrawShape8BitMasked(int iX,int iY,RezFile *pRezFile,Word uRezNum);
	void DrawShape8BitMaskedCentered(RezFile *pRezFile,Word uRezNum);
};
}
namespace Burger {
class RendererSoftware8 : public Renderer {
public:
	RendererSoftware8(void);
	virtual void Draw8BitPixels(int iX,int iY,Word uWidth,Word uHeight,WordPtr uStride,const Word8 *pPixels);
	virtual void Draw8BitPixelsMasked(int iX,int iY,Word uWidth,Word uHeight,WordPtr uStride,const Word8 *pPixels);
	virtual void DrawPixel(int iX,int iY,Word uColorIndex);
	virtual void DrawRect(int iX,int iY,Word uWidth,Word uHeight,Word uColorIndex);
};
}
namespace Burger {
class RendererSoftware16 : public Renderer {
public:
	RendererSoftware16(void);
};
}
namespace Burger {
class Image {
	BURGER_DISABLECOPYCONSTRUCTORS(Image);
public:
	enum eFlags {
		FLAGS_IMAGENOTALLOCATED=0x0020,	///< \ref TRUE if the image pointer was not allocated (And won't be released when Image goes out of scope)
		FLAGS_MIPMAPMASK=0x001F			///< Mask for the number of mip maps present (0 means only one level, max 16)
	};
	enum ePixelTypes {
		PIXELTYPE1BIT=1,			///< 1 bit per pixel monochrome
		PIXELTYPE2BIT=2,			///< 2 bits per pixel indexed by RGB palette
		PIXELTYPE4BIT=4,			///< 4 bits per pixel indexed by RGB palette
		PIXELTYPE332=7,				///< 8 bits per pixel R:3, G:3, B:2
		PIXELTYPE8BIT=8,			///< 8 bits per pixel indexed RGB palette (Or greyscale)
		PIXELTYPE4444=13,			///< 16 bits per pixel native endian A:4, R:4, G:4, B:4
		PIXELTYPE1555=14,			///< 16 bits per pixel native endian A:1, R:5, G:5, B:5
		PIXELTYPE555=15,			///< 16 bits per pixel native endian R:5, G:5, B:5
		PIXELTYPE565=16,			///< 16 bits per pixel native endian R:5, G:6, B:5
		PIXELTYPEDXT1=17,			///< Compressed with DXT1
		PIXELTYPEDXT2=18,			///< Compressed with DXT2
		PIXELTYPEDXT3=19,			///< Compressed with DXT3
		PIXELTYPEDXT4=20,			///< Compressed with DXT4
		PIXELTYPEDXT5=21,			///< Compressed with DXT5
		PIXELTYPE888=24,			///< 24 bits per pixel in bytes of R:8, G:8 and B:8
		PIXELTYPE1010102=31,		///< 32 bits per pixel in bytes of R:10, G:10, B:10 and A:2 in that order
		PIXELTYPE8888=32			///< 32 bits per pixel in bytes of R:8, G:8, B:8 and A:8 in that order
	};
protected:
	Word8 *m_pImage;		///< Pointer to pixel array
	Word m_uStride;			///< Number of bytes per scan line (Likely not the same value as m_uWidth)
	Word m_uWidth;			///< Width of image in pixels
	Word m_uHeight;			///< Height of image in pixels
	Word m_uFlags;			///< Internal behavior flags
	ePixelTypes m_eType;	///< Type of pixel image
public:
	Image();
	~Image();
	static Image * BURGER_API New(void);
	static Image * BURGER_API New(Word uWidth,Word uHeight,ePixelTypes eType);
	static Image * BURGER_API New(Word uWidth,Word uHeight,ePixelTypes eType,Word uMipMaps);
	static Image * BURGER_API New(const Image *pInput);
	void Init(Word uWidth,Word uHeight,ePixelTypes eType,WordPtr uStride,const Word8 *pImage,Word uFlags=0,Word uMipMaps=0);
	Word Init(Word uWidth,Word uHeight,ePixelTypes eType);
	Word Init(Word uWidth,Word uHeight,ePixelTypes eType,Word uMipMaps);
	Word Init(const Image *pInput);
	void Transfer(Image *pInput);
	void Shutdown(void);
	BURGER_INLINE const Word8 *GetImage(void) const { return m_pImage; }
	BURGER_INLINE Word8 *GetImage(void) { return m_pImage; }
	const Word8 *GetImage(Word uMipMap) const;
	BURGER_INLINE Word GetWidth(void) const { return m_uWidth; }
	Word GetWidth(Word uMipMap) const;
	BURGER_INLINE Word GetHeight(void) const { return m_uHeight; }
	Word GetHeight(Word uMipMap) const;
	BURGER_INLINE WordPtr GetStride(void) const { return m_uStride; }
	WordPtr GetStride(Word uMipMap) const;
	BURGER_INLINE ePixelTypes GetType(void) const { return m_eType; }
	Word GetMipMapCount(void) const;
	static Word BURGER_API GetBytesPerPixel(ePixelTypes eType);
	BURGER_INLINE Word GetBytesPerPixel(void) const { return GetBytesPerPixel(m_eType); }
	static Word BURGER_API GetBitsPerPixel(ePixelTypes eType);
	BURGER_INLINE Word GetBitsPerPixel(void) const { return GetBitsPerPixel(m_eType); }
	static WordPtr BURGER_API GetSuggestedStride(Word uWidth,ePixelTypes eType);
	WordPtr GetSuggestedStride(void) const;
	static WordPtr BURGER_API GetSuggestedBufferSize(Word uWidth,Word uHeight,ePixelTypes eType);
	static WordPtr BURGER_API GetSuggestedBufferSize(Word uWidth,Word uHeight,ePixelTypes eType,Word uMipMapLevels);
	WordPtr GetSuggestedBufferSize(void) const;
	WordPtr GetImageSize(Word uMipMap) const;
	const char *ValidateForSave(void) const;
	void ClearBitmap(void);
	Word VerticleFlip(void);
	Word HorizontalFlip(void);
};
}
namespace Burger {
class Display;
class Texture : public ReferenceCounter {
	BURGER_RTTI_IN_CLASS();
public:
	enum eWrapping {
		WRAP_REPEAT,		///< Wrap the texture around
		WRAP_CLAMP			///< Clamp the texture edge
	};
	enum eFilter {
		FILTER_NEAREST,		///< Faster, use nearest pixel
		FILTER_LINEAR		///< Use weighted average for smoothing
	};
	enum eLoader {
		LOADER_LOAD,		///< Command to load a texture into the Image
		LOADER_UNLOAD,		///< Command to release the memory in the Image if allowed
		LOADER_SHUTDOWN		///< Force all memory to be released
	};
	typedef Word (BURGER_API *LoaderProc)(Texture *pThis,eLoader uCommand);	///< Function prototype for loading callback
protected:
	enum eDirtyFlags {
		DIRTY_WRAPPING_S=0x01,	///< Set if the S value was changed
		DIRTY_WRAPPING_T=0x02,	///< Set if the T value was changed
		DIRTY_MIN=0x04,			///< Set if the MIN value was changed
		DIRTY_MAG=0x08,			///< Set if the MAG value was changed
		DIRTY_IMAGE=0x10,		///< Set if the image bitmap was changed
		DIRTY_EXTRA=0x20		///< Flags for derived classes
	};
	LoaderProc m_pLoader;	///< Function to load the image in case of texture purge
	void *m_pUserData;		///< Pointer to user data for the loader
	Texture *m_pNext;		///< Pointer to the next entry
	Texture *m_pPrev;		///< Pointer to the previous entry
#if defined(BURGER_XBOX360)
	D3DTexture *m_pD3DTexture;
#endif
#if defined(BURGER_OPENGL_SUPPORTED) && !defined(BURGER_WINDOWS)
	Word m_uTextureID;		///< OpenGL Texture ID
#endif
	Image m_Image;			///< Description of the texture data
	eWrapping m_eWrappingS;	///< Wrapping setting for the S value
	eWrapping m_eWrappingT;	///< Wrapping setting for the T value
	eFilter m_eMinFilter;	///< Filter for shrinkage
	eFilter m_eMagFilter;	///< Filter for expansion
	Word m_uDirty;			///< Values needed to be updated
	static Texture *g_pHead;	///< Global pointer to the linked list of textures
	void AddToGlobalList(void);
	void RemoveFromGlobalList(void);
public:
	Texture();
	Texture(eWrapping uWrapping,eFilter uFilter);
	virtual ~Texture();
#if defined(BURGER_WINDOWS)
	virtual Word Bind(Display *pDisplay) = 0;
	virtual void Release(Display *pDisplay) = 0;
#else
	Word Bind(Display *pDisplay);
	void Release(Display *pDisplay);
#endif
	Word BURGER_API LoadImageMemory(void);
	void BURGER_API UnloadImageMemory(void);
	void BURGER_API ShutdownImageMemory(void);
	BURGER_INLINE const Image *GetImage(void) const { return &m_Image; }
	BURGER_INLINE Image *GetImage(void) { return &m_Image; }
	BURGER_INLINE const Word8 *GetImage(Word uMipMap) const { return m_Image.GetImage(uMipMap); }
	BURGER_INLINE Word GetWidth(void) const { return m_Image.GetWidth(); }
	BURGER_INLINE Word GetWidth(Word uMipMap) const { return m_Image.GetWidth(uMipMap); }
	BURGER_INLINE Word GetHeight(void) const { return m_Image.GetHeight(); }
	BURGER_INLINE Word GetHeight(Word uMipMap) const { return m_Image.GetHeight(uMipMap); }
	BURGER_INLINE WordPtr GetStride(void) const { return m_Image.GetStride(); }
	BURGER_INLINE WordPtr GetStride(Word uMipMap) const { return m_Image.GetStride(uMipMap); }
	BURGER_INLINE Image::ePixelTypes GetType(void) const { return m_Image.GetType(); }
	BURGER_INLINE Word GetMipMapCount(void) const { return m_Image.GetMipMapCount(); }
	BURGER_INLINE eWrapping GetWrappingS(void) const { return m_eWrappingS; }
	BURGER_INLINE void SetWrappingS(eWrapping uWrapping) { m_eWrappingS = uWrapping; m_uDirty |= DIRTY_WRAPPING_S; }
	BURGER_INLINE eWrapping GetWrappingT(void) const { return m_eWrappingT; }
	BURGER_INLINE void SetWrappingT(eWrapping uWrapping) { m_eWrappingT = uWrapping; m_uDirty |= DIRTY_WRAPPING_T; }
	BURGER_INLINE void SetWrapping(eWrapping uWrapping) { m_eWrappingS = uWrapping; m_eWrappingT = uWrapping; m_uDirty |= (DIRTY_WRAPPING_S|DIRTY_WRAPPING_T);}
	BURGER_INLINE eFilter GetMinFilter(void) const { return m_eMinFilter; }
	BURGER_INLINE void SetMinFilter(eFilter uFilter) { m_eMinFilter = uFilter; m_uDirty |= DIRTY_MIN; }
	BURGER_INLINE eFilter GetMagFilter(void) const { return m_eMagFilter; }
	BURGER_INLINE void SetMagFilter(eFilter uFilter) { m_eMagFilter = uFilter; m_uDirty |= DIRTY_MAG; }
	BURGER_INLINE void SetFilter(eFilter uFilter) { m_eMinFilter = uFilter; m_eMagFilter = uFilter; m_uDirty |= (DIRTY_MIN|DIRTY_MAG); }
	BURGER_INLINE LoaderProc GetLoader(void) const { return m_pLoader; }
	BURGER_INLINE void SetLoader(LoaderProc pCallback) { m_pLoader = pCallback; }
	BURGER_INLINE static Texture *GetFirstTexture(void) { return g_pHead; }
	BURGER_INLINE Texture *GetNext(void) const { return m_pNext; }
	BURGER_INLINE Texture *GetPrevious(void) const { return m_pPrev; }
	void BURGER_API LoadTGA(RezFile *pRezFile,Word uRezNum);
	void BURGER_API LoadTGA(const char *pFilename);
	void BURGER_API LoadPNG(RezFile *pRezFile,Word uRezNum);
	void BURGER_API LoadPNG(const char *pFilename);
	void BURGER_API LoadBMP(RezFile *pRezFile,Word uRezNum);
	void BURGER_API LoadBMP(const char *pFilename);
	static void BURGER_API ReleaseAll(Display *pDisplay);
#if defined(BURGER_XBOX360)
	Word BURGER_API GetD3DFormat(void) const;
	BURGER_INLINE D3DTexture *GetTexture(void) const { return m_pD3DTexture; }
#endif
#if defined(BURGER_OPENGL_SUPPORTED) && !defined(BURGER_WINDOWS)
	static int GetWrapping(eWrapping uWrapping);
	static int GetFilter(eFilter uFilter);
	BURGER_INLINE Word GetTextureID(void) const { return m_uTextureID; }
#endif
private:
	static Word BURGER_API CallbackRezFileTGA(Texture *pTexture,eLoader uLoader);
	static Word BURGER_API CallbackFileTGA(Texture *pTexture,eLoader uLoader);
	static Word BURGER_API CallbackRezFilePNG(Texture *pTexture,eLoader uLoader);
	static Word BURGER_API CallbackFilePNG(Texture *pTexture,eLoader uLoader);
	static Word BURGER_API CallbackRezFileBMP(Texture *pTexture,eLoader uLoader);
	static Word BURGER_API CallbackFileBMP(Texture *pTexture,eLoader uLoader);
};
}
namespace Burger {
class Display;
class VertexBuffer : public ReferenceCounter {
	BURGER_RTTI_IN_CLASS();
public:
	enum eUsage {
		USAGE_COUNTMASK=0x0F,		///< Mask for the element count
		USAGE_CHUNKMASK=0x0F0,		///< Mask for the chunk type
		USAGE_TYPEMASK=0xF00,		///< Mask for the data type
		USAGE_FLOAT=0<<4,			///< Data chunks are floats
		USAGE_USHORT=1<<4,			///< Data chunks are unsigned shorts
		USAGE_POSITION=0<<8,		///< Data type is a position
		USAGE_BLENDWEIGHT=1<<8,		///< Data type is a blend weight
		USAGE_BLENDINDICES=2<<8,	///< Data type is a blend index
		USAGE_NORMAL=3<<8,			///< Data type is a vertex normal
		USAGE_PSIZE=4<<8,			///< Data type is a point size
		USAGE_TEXCOORD=5<<8,		///< Data type is a texture coordinate
		USAGE_TANGENT=6<<8,			///< Data type is a vertex tangent
		USAGE_BINORMAL=7<<8,		///< Data type is a vertex bi-normal
		USAGE_TESSFACTOR=8<<8,		///< Data type is a tessellation factor
		USAGE_POSITIONT=9<<8,		///< Data type is a transformed position
		USAGE_COLOR=10<<8,			///< Data type is a vertex color
		USAGE_FOG=11<<8,			///< Data type is a fog constant
		USAGE_DEPTH=12<<8,			///< Data type is a depth value
		USAGE_SAMPLE=13<<8			///< Data type is a texture value
	};
	struct VertexAoS_t {
		const void *m_pVertexArray;	///< Pointer to the vertex data to upload, if \ref NULL don't upload data
		WordPtr m_uVertexArraySize;	///< Size in bytes of the entire vertex buffer, if 0, don't generate vertex data
		const Word16 *m_pElements;	///< Pointer to the element index data to upload, \ref NULL don't upload data
		WordPtr m_uElementSize;		///< Size in bytes of the entire element buffer, if 0, don't generate an element index array
		const Word *m_pMembers;		///< Pointer to array of array description enumerations
	};
#if defined(BURGER_XBOX360) || defined(DOXYGEN)
protected:
	D3DVertexBuffer * m_pD3DVertexBuffer;			///< (XBox 360 Only) DirectX vertex buffer
	D3DVertexDeclaration *m_pD3DVertexDeclaration;	///< (XBox 360 Only) DirectX vertex array description
	Word m_uStride;									///< (XBox 360 Only) Size in bytes of each entry in the array
	Word m_uArrayEntryCount;						///< (XBox 360 Only) Number of entries in the array
#endif
#if defined(BURGER_OPENGL_SUPPORTED) && !defined(BURGER_WINDOWS)
	Word m_uVertexArrayObjectID;	///< (OpenGL only) Main Vertex Object Array
	Word m_uElementID;				///< (OpenGL only) ID to the index array
	Word m_uBufferID;				///< (OpenGL only) ID for the buffer
	Word m_uArrayEntryCount;		///< (OpenGL only) Number of entries in the array
	Word m_uElementEntryCount;		///< (OpenGL only) Number of entries in the element array
#endif
public:
	VertexBuffer();
	virtual ~VertexBuffer();
#if defined(BURGER_WINDOWS)
	virtual Word LoadData(Display *pDisplay,const VertexAoS_t *pDescription) = 0;
	virtual void ReleaseData(void) = 0;
#else
	Word LoadData(Display *pDisplay,const VertexAoS_t *pDescription);
	void ReleaseData(void);
#endif
#if defined(BURGER_XBOX360) || defined(DOXYGEN)
	BURGER_INLINE D3DVertexBuffer *GetD3DVertexBuffer(void) const { return m_pD3DVertexBuffer; }
	BURGER_INLINE D3DVertexDeclaration *GetD3DVertexDescription(void) const { return m_pD3DVertexDeclaration; }
	BURGER_INLINE Word GetStride(void) const { return m_uStride; }
	BURGER_INLINE Word GetArrayEntryCount(void) const { return m_uArrayEntryCount; }
#endif
#if defined(BURGER_OPENGL_SUPPORTED) && !defined(BURGER_WINDOWS)
	BURGER_INLINE Word GetVertexArrayObject(void) const { return m_uVertexArrayObjectID; }
	BURGER_INLINE Word GetElementID(void) const { return m_uElementID; }
	BURGER_INLINE Word GetBufferID(void) const { return m_uBufferID; }
	BURGER_INLINE Word GetArrayEntryCount(void) const { return m_uArrayEntryCount; }
	BURGER_INLINE Word GetElementEntryCount(void) const { return m_uElementEntryCount; }
#endif
};
}
namespace Burger {
#if defined(BURGER_WINDOWS)
class VertexBufferOpenGL : public VertexBuffer {
	BURGER_RTTI_IN_CLASS();
protected:
	Word m_uVertexArrayObjectID;	///< Main Vertex Object Array
	Word m_uElementID;				///< ID to the index array
	Word m_uBufferID;				///< ID for the buffer
	Word m_uArrayEntryCount;		///< Number of entries in the array
	Word m_uElementEntryCount;		///< Number of entries in the element array
public:
	VertexBufferOpenGL();
	virtual ~VertexBufferOpenGL();
	Word LoadData(Display *pDisplay,const VertexAoS_t *pDescription);
	void ReleaseData(void);
	BURGER_INLINE Word GetVertexArrayObject(void) const { return m_uVertexArrayObjectID; }
	BURGER_INLINE Word GetElementID(void) const { return m_uElementID; }
	BURGER_INLINE Word GetBufferID(void) const { return m_uBufferID; }
	BURGER_INLINE Word GetArrayEntryCount(void) const { return m_uArrayEntryCount; }
	BURGER_INLINE Word GetElementEntryCount(void) const { return m_uElementEntryCount; }
};
#endif
}
namespace Burger {
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
class VertexBufferDirectX9 : public VertexBuffer {
	BURGER_RTTI_IN_CLASS();
protected:
	IDirect3DVertexBuffer9 * m_pVertexBuffer;		///< DirectX vertex buffer
	IDirect3DVertexDeclaration9 *m_pDescription;	///< DirectX vertex array description
	Word m_uStride;									///< Size in bytes of each entry in the array
	Word m_uArrayEntryCount;						///< Number of entries in the array
public:
	VertexBufferDirectX9();
	virtual ~VertexBufferDirectX9();
	virtual Word LoadData(Display *pDisplay,const VertexAoS_t *pDescription);
	virtual void ReleaseData(void);
	BURGER_INLINE IDirect3DVertexBuffer9 *GetDX9VertexBuffer(void) const { return m_pVertexBuffer; }
	BURGER_INLINE IDirect3DVertexDeclaration9 *GetDX9VertexDescription(void) const { return m_pDescription; }
	BURGER_INLINE Word GetStride(void) const { return m_uStride; }
	BURGER_INLINE Word GetArrayEntryCount(void) const { return m_uArrayEntryCount; }
};
#endif
}
namespace Burger {
struct RGBAWord8_t;
class Display : public Base {
	BURGER_DISABLECOPYCONSTRUCTORS(Display);
	BURGER_RTTI_IN_CLASS();
public:
	enum {
		VIDEOMODE_HARDWARE=0x01,	///<  VideoMode_t Set if hardware acceleration is available
		INWINDOW=0x0,				///< The display is in a desktop window, best for debugging
		FULLSCREEN=0x1,				///< Set if full screen
		ALLOWFULLSCREENTOGGLE=0x2,	///< Set if Alt-Enter is allowed to switch from full screen to windowed mode
		ALLOWRESIZING=0x4,			///< On desktop platforms, allow the window to be resized
		FULLPALETTEALLOWED=0x40,	///< Set if all 256 colors of the palette can be used
		STEREO=0x80,				///< Set if 3D Glasses support is enabled
		MULTITHREADED=0x100,		///< Hint that rendering is performed on multiple threads
#if defined(_DEBUG) || defined(DOXYGEN)
		DEFAULTFLAGS=INWINDOW		///< Default window flags (Debug is in a window, release is full screen)
#else
		DEFAULTFLAGS=FULLSCREEN	///< Default window flags (NDEBUG is full screen)
#endif
	};
	enum eClearBits {
		CLEAR_COLOR=0x01,			///< Used by Clear(Word) to clear the color buffer
		CLEAR_DEPTH=0x02,			///< Used by Clear(Word) to clear the depth buffer
		CLEAR_STENCIL=0x04			///< Used by Clear(Word) to clear the stencil buffer
	};
	enum eDepthFunction {
		DEPTHCMP_NEVER,			///< Never render the pixel
		DEPTHCMP_LESS,			///< Render if Z is less than Depth Z
		DEPTHCMP_EQUAL,			///< Render if Z is equal to the Depth Z
		DEPTHCMP_LESSEQUAL,		///< Render if Z is less than or equal to the Depth Z
		DEPTHCMP_GREATER,		///< Render if Z is greater than Depth Z
		DEPTHCMP_NOTEQUAL,		///< Render if Z is not equal to the Depth Z
		DEPTHCMP_GREATEREQUAL,	///< Render if Z is greater than or equal to the Depth Z
		DEPTHCMP_ALWAYS			///< Always render the pixel (Same as turning off depth testing, allows zwrites)
	};
	enum eCullMode {
		CULL_NONE,				///< Don't cull any polygons
		CULL_CLOCKWISE,			///< Don't render clockwise oriented polygons
		CULL_COUNTERCLOCKWISE	///< Don't render counter clockwise oriented polygons
	};
	enum eSourceBlendFactor {
		SRCBLEND_ZERO,					///< Source alpha is forced to zero
		SRCBLEND_ONE,					///< Source alpha is forced to one
		SRCBLEND_COLOR,					///< Source alpha is each color component
		SRCBLEND_ONE_MINUS_COLOR,		///< Source alpha is 1-color component
		SRCBLEND_SRC_ALPHA,				///< Source alpha is the alpha component
		SRCBLEND_ONE_MINUS_SRC_ALPHA,	///< Source alpha is 1-alpha component
		SRCBLEND_DST_ALPHA,				///< Source alpha is the destination buffer alpha component
		SRCBLEND_ONE_MINUS_DST_ALPHA,	///< Source alpha is the destination buffer 1-alpha component
		SRCBLEND_SRC_ALPHA_SATURATE		///< Saturate the alpha with 1
	};
	enum eDestinationBlendFactor {
		DSTBLEND_ZERO,					///< Destination alpha is forced to zero
		DSTBLEND_ONE,					///< Destination alpha is forced to one
		DSTBLEND_COLOR,					///< Destination alpha is each color component
		DSTBLEND_ONE_MINUS_COLOR,		///< Destination alpha is 1-color component
		DSTBLEND_DST_ALPHA,				///< Destination alpha is the alpha component
		DSTBLEND_ONE_MINUS_DST_ALPHA,	///< Destination alpha is 1-alpha component
		DSTBLEND_SRC_ALPHA,				///< Destination alpha is the source buffer alpha component
		DSTBLEND_ONE_MINUS_SRC_ALPHA	///< Destination alpha is the source buffer 1-alpha component
	};
	enum ePrimitiveType {
		PRIM_POINTS,			///< Draw array as points
		PRIM_LINES,				///< Draw array as line end to end pairs
		PRIM_LINESTRIP,			///< Draw array as a long line
		PRIM_TRIANGLES,			///< Draw array as triangles
		PRIM_TRIANGLESTRIP,		///< Draw array as triangle strip
		PRIM_TRIANGLEFAN		///< Draw array as a triangle fan
	};
	struct VideoMode_t {
		Word m_uWidth;		///< Width of video mode
		Word m_uHeight;		///< Height of video mode
		Word m_uDepth;		///< Depth of video mode
		Word m_uHertz;		///< Video scan rate (0 if not supported)
		Word m_uFlags;		///< Hardware/OpenGL
	};
	class VideoCardDescription {
	public:
		SimpleArray<VideoMode_t> m_Array;		///< Array of modes
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
		GUID m_GUID;							///< (Windows only) Device GUID
#endif
#if defined(BURGER_MACOSX) || defined(DOXYGEN)
		NSScreen *m_pNSScreen;					///< (MacOSX only) NSScreen associated with this card
#endif
		String m_DeviceName;					///< Name of the device
		String m_MonitorName;					///< Name of the monitor
		Word m_uDevNumber;						///< Device number
		Word m_bHardwareAccelerated;			///< Is 3D acceleration available?
		VideoCardDescription();
		~VideoCardDescription();
	};
	typedef Word (BURGER_API *FadeProc)(void *pThis,Word uStep);		///< Callback function prototype for palette fading functions
	typedef void (BURGER_API *ResizeProc)(void *pThis,Word uWidth,Word uHeight);		///< Callback function prototype for window resizing
	typedef void (BURGER_API *RenderProc)(void *pThis);					///< Callback function for rendering the scene
	typedef void (BURGER_API *ReleaseProc)(void *pThis);				///< Callback function for releasing resources on shutdown
protected:
	struct Globals_t {
		Word m_uDefaultWidth;			///< Default screen width of the main monitor
		Word m_uDefaultHeight;			///< Default screen height of the main monitor
		Word m_uDefaultDepth;			///< Default screen depth of the main monitor
		Word m_uDefaultHertz;			///< Default screen refresh rate (0 means not applicable)
		Word m_uDefaultTotalWidth;		///< Default screen width of all monitors
		Word m_uDefaultTotalHeight;		///< Default screen height of all monitors
		Word m_uDefaultMonitorCount;	///< Number of monitors attached
#if defined(BURGER_XBOX360)
		Word m_bIsWidescreen;			///< (Xbox 360 Only) \ref TRUE if wide screen display
		Word m_bIsHiDef;				///< (Xbox 360 Only) \ref TRUE if high definition display
		Word m_bIsInterlaced;			///< (Xbox 360 Only) \ref TRUE if interlaced display
#endif
#if defined(BURGER_IOS)
		float m_fRetinaScale;			///< (iOS Only) Points to Pixels scale factor for retina displays
#endif
		Word m_bInitialized;			///< Are the globals set?
	};
	static Globals_t g_Globals;	///< Global values initialized when the first Display class is created
	GameApp *m_pGameApp;		///< Pointer to the game application instance
	Renderer *m_pRenderer;		///< Pointer to a renderer
#if defined(BURGER_XBOX360)
	D3DDevice *m_pD3DDevice;	///< (Xbox 360 Only) Direct 3D device
	Word m_uClearColor;			///< (Xbox 360 Only) 32 bit RGBA color for screen clear
	float m_fClearDepth;		///< (Xbox 360 Only) ZValue to write for screen clear
	Word m_bWideScreen;			///< (Xbox 360 Only) \ref TRUE if wide screen display is active
#endif
#if defined(BURGER_MACOSX) || defined(DOXYGEN)
	NSView *m_pView;							///< (MacOSX Only) Pointer to the main view
	NSWindowController *m_pWindowController;	///< (MacOSX Only) Pointer to the window controller
	NSOpenGLView *m_pOpenGLView;				///< (MacOSX Only) Pointer to the OpenGL view
	_CGLContextObject *m_pOpenGLContext;		///< (MacOSX Only) Pointer to the OpenGL context
	NSWindow *m_pFullScreenWindow;				///< (MacOSX Only) Pointer to the main full screen window
#endif
#if defined(BURGER_IOS) || defined(DOXYGEN)
	EAGLContext *m_pEAGLContext;			///< (iOS Only) OpenGL Context
	Word m_uFrontBuffer;					///< (iOS Only) Main render buffer GL name
	Word m_uColorRenderBuffer;				///< (iOS Only) Color render buffer GL name
	Word m_uDepthRenderBuffer;				///< (iOS Only) Depth buffer for rendering
#endif
#if defined(BURGER_OPENGL_SUPPORTED) && !defined(BURGER_WINDOWS)
public:
	static const Word VERTEX_END = BURGER_MAXUINT;
	struct VertexInputs_t {
		Word m_uIndex;				///< OpenGL BindAttribLocation
		const char *m_pName;		///< Variable name for input
	};
	struct VertexBufferObjectDescription_t {
		const void *m_pPositions;	///< Pointer to the vertex positions
		const void *m_pNormals;		///< Pointer to the vertex normals
		const void *m_pTexcoords;	///< Pointer to the texture UVs
		const void *m_pElements;	///< Pointer to the polygon vertex indexes
		WordPtr m_uPositionSize;	///< Size of the positions in bytes
		WordPtr m_uNormalSize;		///< Size of the vertex normals in bytes
		WordPtr m_uTexcoordSize;	///< Size of the texture UVs in bytes
		WordPtr m_uElementSize;		///< Size of the polygon vertex indexes in bytes
		Word m_ePositionType;		///< Open GL type of positions (GL_FLOAT)
		Word m_uPositionElementCount;	///< Number of elements per position (3 or 4)
		Word m_eNormalType;			///< Open GL type of vertex normal (GL_FLOAT)
		Word m_uNormalElementCount;	///< Number of elements per vertex normal (3 or 4)
		Word m_eTexcoordType;		///< Open GL type of texture UVs (GL_FLOAT)
		Word m_uTexcoordElementCount;	///< Number of elements per uv (2)
	};
	Word *m_pCompressedFormats;				///< Pointer to an array of supported OpenGL compressed textures
	float m_fOpenGLVersion;					///< Numeric value for the version of OpenGL
	float m_fShadingLanguageVersion;		///< Numeric value for the version of the Shader compiler
	float m_fAspectRatio;					///< Width/Height
	float m_fWidth;							///< Width of the rendering target as a float
	float m_fHeight;						///< Height of the rendering target as a float
	Word m_uCompressedFormatCount;			///< Number of supported compressed texture formats
	Word m_uMaximumVertexAttributes;		///< Maximum number of vertex attributes GL_MAX_VERTEX_ATTRIBS
	Word m_uMaximumColorAttachments;		///< Maximum number of color frame attachments GL_MAX_COLOR_ATTACHMENTS
	Word m_uActiveTexture;					///< OpenGL glActiveTexture() shadow value
protected:
#endif
	ResizeProc m_pResize;		///< Callback if the screen changed sizes
	void *m_pResizeData;		///< pThis pointer for m_pResize calls
	RenderProc m_pRender;		///< Callback if the operating system requests a scene draw
	void *m_pRenderData;		///< pThis pointer for m_pRender calls
	ReleaseProc m_pRelease;		///< Callback if the operating system requests a scene draw
	void *m_pReleaseData;		///< pThis pointer for m_pRender calls
	Texture *m_pBoundTextures[8];	///< Bound textures
	Word m_uWidth;				///< Width in pixels of the display buffer
	Word m_uHeight;				///< Height in pixels of the display buffer
	Word m_uDepth;				///< Depth in bits of the display buffer
	Word m_uFlags;				///< Flags for describing available features
	Word m_uDisplayWidth;		///< Width of the display hardware (Can differ from m_uWidth for pixel stretching)
	Word m_uDisplayHeight;		///< Height of the display hardware (Can differ from m_uHeight for pixel stretching)
	Word m_uDisplayDepth;		///< Depth of the display hardware (Can differ from m_uDepth for pixel depth change)
	Word m_uBorderColor;		///< Hardware border color (MSDOS / Amiga only)
	Word m_bPaletteDirty;		///< \ref TRUE if the palette buffer was changed
	Word m_bPaletteVSync;		///< \ref TRUE if palette updates sync to video
	Word m_uPaletteFadeSpeed;	///< Speed in 1/60ths of a second for a palette fade
	Word8 m_Palette[256*3];		///< Palette of 256 RGB values
	static void BURGER_API InitGlobals(void);
	void BURGER_API InitDefaults(GameApp *pGameApp);
public:
	Display(GameApp *pGameApp);
	virtual ~Display();
#if !defined(BURGER_WINDOWS) || defined(DOXYGEN)
#define BURGER_VIRTUAL(a,b,c) a b c;
#else
#define BURGER_VIRTUAL(a,b,c) virtual a b c = 0;
#endif
	BURGER_VIRTUAL(Word,Init,(Word uWidth,Word uHeight,Word uDepth=32,Word uFlags=DEFAULTFLAGS))
	BURGER_VIRTUAL(void,Shutdown,(void))
	BURGER_VIRTUAL(void,BeginScene,(void))
	BURGER_VIRTUAL(void,EndScene,(void))
	BURGER_VIRTUAL(Texture *,CreateTextureObject,(void))
	BURGER_VIRTUAL(VertexBuffer *,CreateVertexBufferObject,(void))
	BURGER_VIRTUAL(void,SetViewport,(Word uX,Word uY,Word uWidth,Word uHeight))
	BURGER_VIRTUAL(void,SetClearColor,(float fRed,float fGreen,float fBlue,float fAlpha))
	BURGER_VIRTUAL(void,SetClearDepth,(float fDepth))
	BURGER_VIRTUAL(void,Clear,(Word uMask))
	BURGER_VIRTUAL(void,Bind,(Texture *pTexture,Word uIndex=0))
	BURGER_VIRTUAL(void,SetBlend,(Word bEnable))
	BURGER_VIRTUAL(void,SetBlendFunction,(eSourceBlendFactor uSourceFactor,eDestinationBlendFactor uDestFactor))
	BURGER_VIRTUAL(void,SetLighting,(Word bEnable))
	BURGER_VIRTUAL(void,SetZWrite,(Word bEnable))
	BURGER_VIRTUAL(void,SetDepthTest,(eDepthFunction uDepthFunction))
	BURGER_VIRTUAL(void,SetCullMode,(eCullMode uCullMode))
	BURGER_VIRTUAL(void,DrawPrimitive,(ePrimitiveType uPrimitiveType,VertexBuffer *pVertexBuffer))
	BURGER_VIRTUAL(void,DrawElements,(ePrimitiveType uPrimitiveType,VertexBuffer *pVertexBuffer))
#if defined(BURGER_XBOX360) || defined(DOXYGEN)
	D3DVertexShader * BURGER_API CreateVertexShader(const void *pVertexShaderBinary) const;
	D3DPixelShader * BURGER_API CreatePixelShader(const void *pPixelShaderBinary) const;
	BURGER_INLINE D3DDevice *GetD3DDevice(void) const { return m_pD3DDevice; }
	void BURGER_API InitState(void);
	BURGER_INLINE Word IsWideScreen(void) { return g_Globals.m_bIsWidescreen; }
	BURGER_INLINE Word IsHiDef(void) { return g_Globals.m_bIsHiDef; }
	BURGER_INLINE Word IsInterlaced(void) { return g_Globals.m_bIsInterlaced; }
#endif
#if defined(BURGER_MACOSX) || defined(DOXYGEN)
	BURGER_INLINE NSView *GetView(void) const { return m_pView; }
	BURGER_INLINE NSWindowController *GetWindowController(void) const { return m_pWindowController; }
	BURGER_INLINE NSOpenGLView *GetOpenGLView(void) const { return m_pOpenGLView; }
	BURGER_INLINE _CGLContextObject *GetOpenGLContext(void) const { return m_pOpenGLContext; }
	BURGER_INLINE NSWindow *GetFullScreenWindow(void) const { return m_pFullScreenWindow; }
	BURGER_INLINE void SetFullScreenWindow(NSWindow *pFullScreenWindow) { m_pFullScreenWindow = pFullScreenWindow; }
#endif
#if defined(BURGER_IOS) || defined(DOXYGEN)
	BURGER_INLINE EAGLContext *GetGLContext(void) const { return m_pEAGLContext; }
	BURGER_INLINE Word GetFrontBuffer(void) const { return m_uFrontBuffer; }
	BURGER_INLINE Word GetColorBuffer(void) const { return m_uColorRenderBuffer; }
	BURGER_INLINE Word GetDepthBuffer(void) const { return m_uDepthRenderBuffer; }
	BURGER_INLINE static float GetRetinaScale(void) { return g_Globals.m_fRetinaScale; }
#else
	BURGER_INLINE static Word GetFrontBuffer(void) { return 0; }
#endif
#if defined(BURGER_OPENGL_SUPPORTED) && !defined(BURGER_WINDOWS)
	BURGER_INLINE float GetOpenGLVersion(void) const { return m_fOpenGLVersion; }
	BURGER_INLINE float GetShadingLanguageVersion(void) const { return m_fShadingLanguageVersion; }
	BURGER_INLINE Word GetCompressedFormatCount(void) const { return m_uCompressedFormatCount; }
	BURGER_INLINE const Word *GetCompressedFormats(void) const { return m_pCompressedFormats; }
	BURGER_INLINE Word GetMaximumVertexAttributes(void) const { return m_uMaximumVertexAttributes; }
	void BURGER_API SetupOpenGL(void);
	Word BURGER_API CompileShader(Word GLEnum,const char *pShaderCode,WordPtr uShaderCodeLength=0) const;
	Word BURGER_API CompileProgram(const char *pUnifiedShader,WordPtr uLength,const VertexInputs_t *pVertexInputs=NULL,const Word *pMembers=NULL) const;
	Word BURGER_API CompileProgram(const char *pVertexShader,WordPtr uVSLength,const char *pPixelShader,WordPtr uPSLength,const VertexInputs_t *pVertexInputs=NULL,const Word *pMembers=NULL) const;
	Word BURGER_API CreateVertexArrayObject(const VertexBufferObjectDescription_t *pDescription) const;
	void BURGER_API DeleteVertexArrayObject(Word uVertexArrayObject) const;
	Word BURGER_API BuildFrameBufferObject(Word uWidth,Word uHeight,Word uGLDepth,Word uGLClamp,Word uGLZDepth=0) const;
	static void BURGER_API DeleteFrameBufferObjectAttachment(Word uAttachment);
	void BURGER_API DeleteFrameBufferObject(Word uFrameBufferObject) const;
	static Word BURGER_API CreateTextureID(const Image *pImage,Word bGenerateMipMap=FALSE);
	static const char * BURGER_API GetErrorString(Word uGLErrorEnum);
	static WordPtr BURGER_API GetGLTypeSize(Word uGLTypeEnum);
	static Word BURGER_API PrintGLError(const char *pErrorLocation);
#endif
	BURGER_INLINE Texture *GetBoundTexture(Word uIndex=0) const { return m_pBoundTextures[uIndex]; }
	Texture * BURGER_API CreateTexture(Texture::eWrapping uWrapping,Texture::eFilter uFilter);
	VertexBuffer * BURGER_API CreateVertexBuffer(const VertexBuffer::VertexAoS_t *pDescription);
	static Word BURGER_API GetVideoModes(ClassArray<VideoCardDescription> *pOutput);
	void BURGER_API SetPalette(Word uStart,Word uCount,const Word8 *pPalette);
	void BURGER_API SetPalette(Word uStart,Word uCount,const RGBAWord8_t *pPalette);
	void BURGER_API SetBorderColor(Word uColor);
	void BURGER_API SetWindowTitle(const char *pTitle);
	void BURGER_API SetPaletteBlack(void);
	void BURGER_API SetPaletteWhite(void);
	void BURGER_API SetPalette(const Word8 *pPalette);
	void BURGER_API SetPalette(const RGBAWord8_t *pPalette);
	void BURGER_API SetPalette(void **pHandle);
	void BURGER_API SetPalette(RezFile *pRez,Word uResID);
	void BURGER_API SetPalette(Word uStart,Word uCount,RezFile *pRez,Word uResID);
	void BURGER_API FadeTo(const Word8 *pPalette,FadeProc pProc=NULL,void *pData=NULL);
	void BURGER_API FadeToBlack(FadeProc pProc=NULL,void *pData=NULL);
	void BURGER_API FadeToWhite(FadeProc pProc=NULL,void *pData=NULL);
	void BURGER_API FadeTo(RezFile *pRez,Word uResID,FadeProc pProc=NULL,void *pData=NULL);
	void BURGER_API FadeTo(void **pHandle,FadeProc pProc=NULL,void *pData=NULL);
	BURGER_INLINE static Word GetDefaultWidth(void) { return g_Globals.m_uDefaultWidth; }
	BURGER_INLINE static Word GetDefaultHeight(void) { return g_Globals.m_uDefaultHeight; }
	BURGER_INLINE static Word GetDefaultDepth(void) { return g_Globals.m_uDefaultDepth; }
	BURGER_INLINE static Word GetDefaultHertz(void) { return g_Globals.m_uDefaultHertz; }
	BURGER_INLINE static Word GetDefaultTotalWidth(void) { return g_Globals.m_uDefaultTotalWidth; }
	BURGER_INLINE static Word GetDefaultTotalHeight(void) { return g_Globals.m_uDefaultTotalHeight; }
	BURGER_INLINE static Word GetDefaultMonitorCount(void) { return g_Globals.m_uDefaultMonitorCount; }
	BURGER_INLINE GameApp *GetGameApp(void) const { return m_pGameApp; }
	BURGER_INLINE Word GetWidth(void) const { return m_uWidth; }
	BURGER_INLINE Word GetHeight(void) const { return m_uHeight; }
	BURGER_INLINE Word GetDepth(void) const { return m_uDepth; }
	BURGER_INLINE Word GetFlags(void) const { return m_uFlags; }
	BURGER_INLINE Word GetDisplayWidth(void) const { return m_uDisplayWidth; }
	BURGER_INLINE Word GetDisplayHeight(void) const { return m_uDisplayHeight; }
	BURGER_INLINE const Word8 *GetPalette(void) const { return m_Palette; }
	BURGER_INLINE Word GetBorderColor(void) const { return m_uBorderColor; }
	BURGER_INLINE Word GetFadeSpeed(void) const { return m_uPaletteFadeSpeed; }
	BURGER_INLINE void SetFadeSpeed(Word uPaletteFadeSpeed) { m_uPaletteFadeSpeed = uPaletteFadeSpeed; }
	BURGER_INLINE Word GetPaletteVSync(void) const { return m_bPaletteVSync; }
	BURGER_INLINE void SetPaletteVSync(Word bPaletteVSync) { m_bPaletteVSync=bPaletteVSync; }
	BURGER_INLINE void SetResizeCallback(ResizeProc pResize,void *pResizeData) { m_pResize = pResize; m_pResizeData=pResizeData; }
	BURGER_INLINE ResizeProc GetResizeCallback(void) const { return m_pResize; }
	BURGER_INLINE void *GetResizeCallbackData(void) const { return m_pResizeData; }
	BURGER_INLINE void SetRenderCallback(RenderProc pRender,void *pRenderData) { m_pRender = pRender; m_pRenderData=pRenderData; }
	BURGER_INLINE RenderProc GetRenderCallback(void) const { return m_pRender; }
	BURGER_INLINE void *GetRenderCallbackData(void) const { return m_pRenderData; }
	BURGER_INLINE void SetReleaseCallback(ReleaseProc pRelease,void *pReleaseData) { m_pRelease = pRelease; m_pReleaseData=pReleaseData; }
	BURGER_INLINE ReleaseProc GetReleaseCallback(void) const { return m_pRelease; }
	BURGER_INLINE void *GetReleaseCallbackData(void) const { return m_pReleaseData; }
};
#undef BURGER_VIRTUAL
}
namespace Burger {
class Image;
#if defined(BURGER_WINDOWS)
class DisplayOpenGL : public Display {
	BURGER_RTTI_IN_CLASS();
public:
	static const Word VERTEX_END = BURGER_MAXUINT;
	struct VertexInputs_t {
		Word m_uIndex;				///< OpenGL BindAttribLocation
		const char *m_pName;		///< Variable name for input
	};
	struct VertexBufferObjectDescription_t {
		const void *m_pPositions;	///< Pointer to the vertex positions
		const void *m_pNormals;		///< Pointer to the vertex normals
		const void *m_pTexcoords;	///< Pointer to the texture UVs
		const void *m_pElements;	///< Pointer to the polygon vertex indexes
		WordPtr m_uPositionSize;	///< Size of the positions in bytes
		WordPtr m_uNormalSize;		///< Size of the vertex normals in bytes
		WordPtr m_uTexcoordSize;	///< Size of the texture UVs in bytes
		WordPtr m_uElementSize;		///< Size of the polygon vertex indexes in bytes
		Word m_ePositionType;		///< Open GL type of positions (GL_FLOAT)
		Word m_uPositionElementCount;	///< Number of elements per position (3 or 4)
		Word m_eNormalType;			///< Open GL type of vertex normal (GL_FLOAT)
		Word m_uNormalElementCount;	///< Number of elements per vertex normal (3 or 4)
		Word m_eTexcoordType;		///< Open GL type of texture UVs (GL_FLOAT)
		Word m_uTexcoordElementCount;	///< Number of elements per uv (2)
	};
protected:
	Word *m_pCompressedFormats;		///< Pointer to an array of supported OpenGL compressed textures
	HDC__ *m_pOpenGLDeviceContext;	///< (Windows only) Window to attach the GL context to
	HGLRC__ *m_pOpenGLContext;		///< (Windows only) Current OpenGL context
	Word m_bResolutionChanged;		///< (Windows only) Set to \ref TRUE if the display needs to be restored
	float m_fOpenGLVersion;					///< Numeric value for the version of OpenGL
	float m_fShadingLanguageVersion;		///< Numeric value for the version of the Shader compiler
	float m_fAspectRatio;					///< Width/Height
	float m_fWidth;							///< Width of the rendering target as a float
	float m_fHeight;						///< Height of the rendering target as a float
	Word m_uCompressedFormatCount;			///< Number of supported compressed texture formats
	Word m_uMaximumVertexAttributes;		///< Maximum number of vertex attributes GL_MAX_VERTEX_ATTRIBS
	Word m_uMaximumColorAttachments;		///< Maximum number of color frame attachments GL_MAX_COLOR_ATTACHMENTS
	Word m_uActiveTexture;					///< OpenGL glActiveTexture() shadow value
public:
	DisplayOpenGL(GameApp *pGameApp);
	virtual Word Init(Word uWidth,Word uHeight,Word uDepth=32,Word uFlags=DEFAULTFLAGS);
	virtual void Shutdown(void);
	virtual void BeginScene(void);
	virtual void EndScene(void);
	virtual Texture *CreateTextureObject(void);
	virtual VertexBuffer *CreateVertexBufferObject(void);
	virtual void SetViewport(Word uX,Word uY,Word uWidth,Word uHeight);
	virtual void SetClearColor(float fRed,float fGreen,float fBlue,float fAlpha);
	virtual void SetClearDepth(float fDepth);
	virtual void Clear(Word uMask);
	virtual void Bind(Texture *pTexture,Word uIndex=0);
	virtual void SetBlend(Word bEnable);
	virtual void SetBlendFunction(eSourceBlendFactor uSourceFactor,eDestinationBlendFactor uDestFactor);
	virtual void SetLighting(Word bEnable);
	virtual void SetZWrite(Word bEnable);
	virtual void SetDepthTest(eDepthFunction uDepthFunction);
	virtual void SetCullMode(eCullMode uCullMode);
	virtual void DrawPrimitive(ePrimitiveType uPrimitiveType,VertexBuffer *pVertexBuffer);
	virtual void DrawElements(ePrimitiveType uPrimitiveType,VertexBuffer *pVertexBuffer);
	BURGER_INLINE float GetOpenGLVersion(void) const { return m_fOpenGLVersion; }
	BURGER_INLINE float GetShadingLanguageVersion(void) const { return m_fShadingLanguageVersion; }
	BURGER_INLINE Word GetCompressedFormatCount(void) const { return m_uCompressedFormatCount; }
	BURGER_INLINE const Word *GetCompressedFormats(void) const { return m_pCompressedFormats; }
	BURGER_INLINE Word GetMaximumVertexAttributes(void) const { return m_uMaximumVertexAttributes; }
	void BURGER_API SetupOpenGL(void);
	Word BURGER_API CompileShader(Word GLEnum,const char *pShaderCode,WordPtr uShaderCodeLength=0) const;
	Word BURGER_API CompileProgram(const char *pUnifiedShader,WordPtr uLength,const VertexInputs_t *pVertexInputs=NULL,const Word *pMembers=NULL) const;
	Word BURGER_API CompileProgram(const char *pVertexShader,WordPtr uVSLength,const char *pPixelShader,WordPtr uPSLength,const VertexInputs_t *pVertexInputs=NULL,const Word *pMembers=NULL) const;
	Word BURGER_API CreateVertexArrayObject(const VertexBufferObjectDescription_t *pDescription) const;
	void BURGER_API DeleteVertexArrayObject(Word uVertexArrayObject) const;
	Word BURGER_API BuildFrameBufferObject(Word uWidth,Word uHeight,Word uGLDepth,Word uGLClamp,Word uGLZDepth=0) const;
	static void BURGER_API DeleteFrameBufferObjectAttachment(Word uAttachment);
	void BURGER_API DeleteFrameBufferObject(Word uFrameBufferObject) const;
	static Word BURGER_API CreateTextureID(const Image *pImage,Word bGenerateMipMap=FALSE);
	static const char * BURGER_API GetErrorString(Word uGLErrorEnum);
	static WordPtr BURGER_API GetGLTypeSize(Word uGLTypeEnum);
	static Word BURGER_API PrintGLError(const char *pErrorLocation);
	static void BURGER_API WindowsLink(void);
	static void BURGER_API WindowsUnlink(void);
	BURGER_INLINE static Word GetFrontBuffer(void) { return 0; }
};
#endif
}
namespace Burger {
#if defined(BURGER_OPENGL_SUPPORTED)
#if defined(BURGER_WINDOWS)
class DisplayOpenGLSoftware8 : public DisplayOpenGL {
#else
class DisplayOpenGLSoftware8 : public Display {
#endif
	void *m_pBitMap;				///< Pointer the the HBITMAP's bitmap
	RendererSoftware8 m_Renderer;	///< Software renderer context
	Word m_uBitMapTexture;			///< OpenGL Texture for the bitmap
	Word m_uPaletteTexture;			///< OpenGL Texture for the palette
	Word m_uProgram;				///< OpenGL shader program
	Word m_uVertexShader;			///< OpenGL vertex shader subroutine
	Word m_uFragmentShader;			///< OpenGL fragment shader subroutine
	Word m_uvPositionHandle;		///< OpenGL shader handle for shader vertexes
	Word m_uUVHandle;				///< OpenGL shader handle for texture UV coordinates
	BURGER_RTTI_IN_CLASS();
public:
	DisplayOpenGLSoftware8(GameApp *pGameApp);
	virtual Word Init(Word uWidth,Word uHeight,Word uDepth=8,Word uFlags=DEFAULTFLAGS);
	virtual void Shutdown(void);
	virtual void BeginScene(void);
	virtual void EndScene(void);
	BURGER_INLINE RendererSoftware8 *GetRenderer(void) { return &m_Renderer; }
};
#endif
}
namespace Burger {
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
class DisplayDirectX9 : public Display {
public:
	enum {
		DIRECTXRESETATTEMPTS=30			///< Number of times the app will retry restarting the display before giving up
	};
protected:
	IDirect3D9 *m_pDirect3D9;				///< Pointer to the Direct3D9 context
	IDirect3DDevice9 *m_pDirect3DDevice9;	///< Pointer to the Direct3D9 device
	IDirect3DSurface9 *m_pDefaultRenderTarget;
	IDirect3DSurface9 *m_pCurrentRenderTarget;
	Word m_bLostDevice;					///< TRUE if the device was lost (Minimized?)
	Word m_bPower2Textures;				///< TRUE if only power of two textures are allowed
	Word m_bVSynced;					///< TRUE if presentation is synced to VBlank
	Word m_bMultiRenderTargets;			///< TRUE if multiple render targets are supported
	Word m_bSeparateAlphaBlend;			///< TRUE if separated alpha blending is supported
	Word m_bSceneBegun;					///< TRUE if BeginScene() was called
	Word m_uBackBufferFormat;			///< Requested back buffer format
	Word m_uMaxTextureWidth;
	Word m_uMaxTextureHeight;
	Word m_uClearColor;
	float m_fClearDepth;
	void BURGER_API CreatePresentParameters(_D3DPRESENT_PARAMETERS_ *pOutput);
	void BURGER_API InitState(void);
	Word BURGER_API Reset(void);
public:
	DisplayDirectX9(GameApp *pGameApp);
	~DisplayDirectX9();
	virtual Word Init(Word uWidth,Word uHeight,Word uDepth=32,Word uFlags=DEFAULTFLAGS);
	virtual void Shutdown(void);
	virtual void BeginScene(void);
	virtual void EndScene(void);
	virtual Texture *CreateTextureObject(void);
	virtual VertexBuffer *CreateVertexBufferObject(void);
	virtual void SetViewport(Word uX,Word uY,Word uWidth,Word uHeight);
	virtual void SetClearColor(float fRed,float fGreen,float fBlue,float fAlpha);
	virtual void SetClearDepth(float fDepth);
	virtual void Clear(Word uMask);
	virtual void Bind(Texture *pTexture,Word uIndex=0);
	virtual void SetBlend(Word bEnable);
	virtual void SetBlendFunction(eSourceBlendFactor uSourceFactor,eDestinationBlendFactor uDestFactor);
	virtual void SetLighting(Word bEnable);
	virtual void SetZWrite(Word bEnable);
	virtual void SetDepthTest(eDepthFunction uDepthFunction);
	virtual void SetCullMode(eCullMode uCullMode);
	virtual void DrawPrimitive(ePrimitiveType uPrimitiveType,VertexBuffer *pVertexBuffer);
	virtual void DrawElements(ePrimitiveType uPrimitiveType,VertexBuffer *pVertexBuffer);
	IDirect3DVertexShader9 * BURGER_API CreateVertexShader(const void *pVertexShaderBinary) const;
	IDirect3DPixelShader9 * BURGER_API CreatePixelShader(const void *pPixelShaderBinary) const;
	BURGER_INLINE IDirect3D9 *GetDirect3D9(void) const { return m_pDirect3D9; }
	BURGER_INLINE IDirect3DDevice9 *GetDirect3DDevice9(void) const { return m_pDirect3DDevice9; }
};
#endif
}
namespace Burger {
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
class DisplayDirectX9Software8 : public DisplayDirectX9 {
protected:
	IDirect3DPixelShader9 *m_pPixelShader8Bit;	///< Pointer to the 8 bit pixel shader
	IDirect3DTexture9 *m_pBitMapTextureSysMem;	///< Texture for the 8 bit offscreen buffer
	IDirect3DTexture9 *m_pBitMapTexture;		///< Texture for the 8 bit video memory buffer
	IDirect3DTexture9 *m_pPaletteTexture;		///< Texture for the palette
	IDirect3DVertexBuffer9 *m_pVertexBuffer;	///< Vertex buffer to blit the software buffer to hardware
	RendererSoftware8 m_Renderer;				///< Software renderer context
	Word m_bFrontBufferTrueColor;				///< \ref TRUE if the front buffer is true color (Not 8 bit paletted)
	Word m_uResetAttempts;						///< Number of tries to restore the video display
	void FillVertexBuffer(void);
	long AllocateResources(void);
	void ReleaseResources(void);
	long ResetLostDevice(void);
public:
	DisplayDirectX9Software8(GameApp *pGameApp);
	virtual Word Init(Word uWidth,Word uHeight,Word uDepth=32,Word uFlags=DEFAULTFLAGS);
	virtual void Shutdown(void);
	virtual void BeginScene(void);
	virtual void EndScene(void);
	BURGER_INLINE Renderer *GetRenderer(void) { return &m_Renderer; }
};
#endif
}
namespace Burger {
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
class DisplayDIB : public Display {
public:
	DisplayDIB(GameApp *pGameApp);
protected:
	virtual Word InitContext(void);
	virtual void PostShutdown(void);
	virtual void PostEndScene(void);
	HDC__ *m_pWindowDC;				///< Pointer to the window's device contect
	HDC__ *m_pBitMapDC;				///< Pointer to the BitMap's device contect
};
#endif
}
namespace Burger {
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
class DisplayDIBSoftware8 : public DisplayDIB {
public:
	DisplayDIBSoftware8(GameApp *pGameApp);
protected:
	virtual Word InitContext(void);
	virtual void PostShutdown(void);
	virtual void PostEndScene(void);
private:
	void *m_pBitMap;				///< Pointer the the HBITMAP's bitmap
	HPALETTE__ *m_pHPalette;		///< Pointer to the HPALETTE for this window
	HBITMAP__ *m_pHBitMap;			///< Pointer to the frame HBITMAP
	RendererSoftware8 m_Renderer;	///< Software renderer context
};
#endif
}
namespace Burger {
struct RGBWord8_t {
	Word8 m_uRed;	///< 8 bit red value
	Word8 m_uGreen;	///< 8 bit green value
	Word8 m_uBlue;	///< 8 bit blue value
	static const RGBWord8_t Aqua;
	static const RGBWord8_t Black;
	static const RGBWord8_t Blue;
	static const RGBWord8_t Fuchsia;
	static const RGBWord8_t Gray;
	static const RGBWord8_t Green;
	static const RGBWord8_t Lime;
	static const RGBWord8_t Maroon;
	static const RGBWord8_t Navy;
	static const RGBWord8_t Olive;
	static const RGBWord8_t Orange;
	static const RGBWord8_t Purple;
	static const RGBWord8_t Red;
	static const RGBWord8_t Silver;
	static const RGBWord8_t Teal;
	static const RGBWord8_t White;
	static const RGBWord8_t Yellow;
	void BURGER_API Interpolate(const RGBWord8_t *pFrom,const RGBWord8_t *pTo,float fFactor);
};
struct RGBAWord8_t {
	Word8 m_uRed;	///< 8 bit red value
	Word8 m_uGreen;	///< 8 bit green value
	Word8 m_uBlue;	///< 8 bit blue value
	Word8 m_uAlpha;	///< 8 bit alpha value
	static const RGBAWord8_t Aqua;
	static const RGBAWord8_t Black;
	static const RGBAWord8_t Blue;
	static const RGBAWord8_t Fuchsia;
	static const RGBAWord8_t Gray;
	static const RGBAWord8_t Green;
	static const RGBAWord8_t Lime;
	static const RGBAWord8_t Maroon;
	static const RGBAWord8_t Navy;
	static const RGBAWord8_t Olive;
	static const RGBAWord8_t Orange;
	static const RGBAWord8_t Purple;
	static const RGBAWord8_t Red;
	static const RGBAWord8_t Silver;
	static const RGBAWord8_t Teal;
	static const RGBAWord8_t White;
	static const RGBAWord8_t Yellow;
	void BURGER_API Interpolate(const RGBAWord8_t *pFrom,const RGBAWord8_t *pTo,float fFactor);
};
struct RGBWord16_t {
	Word16 m_uRed;		///< 16 bit red value
	Word16 m_uGreen;	///< 16 bit green value
	Word16 m_uBlue;		///< 16 bit blue value
};
struct RGBAWord16_t {
	Word16 m_uRed;		///< 16 bit red value
	Word16 m_uGreen;	///< 16 bit green value
	Word16 m_uBlue;		///< 16 bit blue value
	Word16 m_uAlpha;	///< 16 bit alpha value
};
struct RGBFloat_t {
	float m_fRed;	///< 32 bit float red value
	float m_fGreen;	///< 32 bit float green value
	float m_fBlue;	///< 32 bit float blue value
	static const RGBFloat_t Aqua;
	static const RGBFloat_t Black;
	static const RGBFloat_t Blue;
	static const RGBFloat_t Fuchsia;
	static const RGBFloat_t Gray;
	static const RGBFloat_t Green;
	static const RGBFloat_t Lime;
	static const RGBFloat_t Maroon;
	static const RGBFloat_t Navy;
	static const RGBFloat_t Olive;
	static const RGBFloat_t Orange;
	static const RGBFloat_t Purple;
	static const RGBFloat_t Red;
	static const RGBFloat_t Silver;
	static const RGBFloat_t Teal;
	static const RGBFloat_t White;
	static const RGBFloat_t Yellow;
	BURGER_INLINE operator Vector3D_t &() { return *reinterpret_cast<Vector3D_t *>(this); }
	BURGER_INLINE operator const Vector3D_t &() const { return *reinterpret_cast<const Vector3D_t *>(this); }
	BURGER_INLINE RGBFloat_t &operator = (const Vector3D_t &rInput) { *this = *reinterpret_cast<const RGBFloat_t *>(&rInput); return *this; }
	void BURGER_API HSLInterpolate(const RGBFloat_t *pInput1,const RGBFloat_t *pInput2,float fFactor,Word bDirection=FALSE);
};
struct RGBAFloat_t {
	float m_fRed;	///< 32 bit float red value
	float m_fGreen;	///< 32 bit float green value
	float m_fBlue;	///< 32 bit float blue value
	float m_fAlpha;	///< 32 bit float alpha value
	static const RGBAFloat_t Aqua;
	static const RGBAFloat_t Black;
	static const RGBAFloat_t Blue;
	static const RGBAFloat_t Fuchsia;
	static const RGBAFloat_t Gray;
	static const RGBAFloat_t Green;
	static const RGBAFloat_t Lime;
	static const RGBAFloat_t Maroon;
	static const RGBAFloat_t Navy;
	static const RGBAFloat_t Olive;
	static const RGBAFloat_t Orange;
	static const RGBAFloat_t Purple;
	static const RGBAFloat_t Red;
	static const RGBAFloat_t Silver;
	static const RGBAFloat_t Teal;
	static const RGBAFloat_t White;
	static const RGBAFloat_t Yellow;
	BURGER_INLINE operator Vector4D_t &() { return *reinterpret_cast<Vector4D_t *>(this); }
	BURGER_INLINE operator const Vector4D_t &() const { return *reinterpret_cast<const Vector4D_t *>(this); }
	BURGER_INLINE RGBAFloat_t &operator = (const Vector4D_t &rInput) { *this = *reinterpret_cast<const RGBAFloat_t *>(&rInput); return *this; }
};
struct HSL_t {
	float m_fHue;			///< 32 bit float hue 0 to 1.0f
	float m_fSaturation;	///< 32 bit float saturation 0 to 1.0f
	float m_fLuminance;		///< 32 bit float luminance 0 to 1.0f
	void BURGER_API Interpolate(const HSL_t *pInput1,const HSL_t *pInput2,float fFactor,Word bDirection=FALSE);
};
class Palette {
public:
	struct RGBColorList {
		Word8 m_uCount;			///< Number of entries
		RGBWord8_t Colors[1];	///< Actual data to set
	};
	static void BURGER_API FromRGB15(RGBWord8_t *pOutput,Word uInput);
	static void BURGER_API FromRGB15(RGBAWord8_t *pOutput,Word uInput);
	static void BURGER_API FromRGB1555(RGBAWord8_t *pOutput,Word uInput);
	static void BURGER_API FromRGB16(RGBWord8_t *pOutput,Word uInput);
	static void BURGER_API FromRGB16(RGBAWord8_t *pOutput,Word uInput);
	static Word BURGER_API ToRGB15(const RGBWord8_t *pInput);
	static Word BURGER_INLINE ToRGB15(const RGBAWord8_t *pInput) { return ToRGB15(reinterpret_cast<const RGBWord8_t*>(pInput)); }
	static Word BURGER_API ToRGB16(const RGBWord8_t *pInput);
	static Word BURGER_INLINE ToRGB16(const RGBAWord8_t *pInput) { return ToRGB16(reinterpret_cast<const RGBWord8_t*>(pInput)); }
	static Word BURGER_API ToDisplay(const RGBWord8_t *pInput,const Display *pDisplay);
	static Word BURGER_API ToDisplay(Word uRed,Word uGreen,Word uBlue,const Display *pDisplay);
	static Word BURGER_API ToDisplay(Word32 uRGBColor,const Display *pDisplay);
	static Word BURGER_API FindColorIndex(const Word8 *pPalette,Word uRed,Word uGreen,Word uBlue,Word uCount);
	static void BURGER_API Make8BitLookupTable(Word *pOutput,const Word8 *pInput,const Display *pDisplay);
	static void BURGER_API Make8BitLookupTable(Word *pOutput,RezFile *pInput,Word uRezNum,const Display *pDisplay);
	static void BURGER_API MakeRemapLookup(Word8 *pOutput,const Word8 *pNewPalette,const Word8 *pOldPalette);
	static void BURGER_API MakeRemapLookupMasked(Word8 *pOutput,const Word8 *pNewPalette,const Word8 *pOldPalette);
	static void BURGER_API MakeColorMasks(Word8 *pOutput,Word uMaskIndex);
	static void BURGER_API MakeFadeLookup(Word8 *pOutput,const Word8 *pInput,Word uRedAdjust,Word uGreenAdjust,Word uBlueAdjust);
};
BURGER_INLINE void CopyPalette(RGBWord8_t *pOutput,const RGBWord8_t *pInput,Word uEntries=256) { MemoryCopy(pOutput,pInput,uEntries*sizeof(RGBWord8_t)); }
extern void BURGER_API CopyPalette(RGBWord8_t *pOutput,const RGBAWord8_t *pInput,Word uEntries=256);
extern void BURGER_API CopyPalette(RGBAWord8_t *pOutput,const RGBWord8_t *pInput,Word uEntries=256);
BURGER_INLINE void CopyPalette(RGBAWord8_t *pOutput,const RGBAWord8_t *pInput,Word uEntries=256) { MemoryCopy(pOutput,pInput,uEntries*sizeof(RGBAWord8_t)); }
extern void BURGER_API Convert(RGBFloat_t *pOutput,const HSL_t *pInput);
extern void BURGER_API Convert(HSL_t *pOutput,const RGBFloat_t *pInput);
}
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
namespace Burger {
class WindowsApp : public GameApp {
public:
	typedef Word (BURGER_API *MainWindowProc)(WindowsApp *pThis,HWND__ *hWnd,Word uMessage,WordPtr wParam,WordPtr lParam,WordPtr *pOutput);	///< Callback custom window message handler
private:
	HINSTANCE__ *m_hInstance;		///< Current instance of the application
	HWND__ *m_hWindow;				///< Main window for the application
	HICON__ *m_pDefaultCursor;		///< Default cursor when not in the game area
	const char **m_ppOldArgv;		///< Saved pointer to the global __argv for restoring on exit
	MainWindowProc m_pCallBack;		///< Custom application window proc
	int m_iPreviousWindowX;			///< Previous X coordinate of the window
	int m_iPreviousWindowY;			///< Previous Y coordinate of the window
	Word m_bPreviousWindowXYValid;	///< \ref TRUE if m_iPreviousWindowX was initialized
	Word16 m_uAtom;					///< Atom assigned to my class
	BURGER_DISABLECOPYCONSTRUCTORS(WindowsApp);
public:
	static void BURGER_API OutputWindowsMessage(Word uMessage,WordPtr wParam,WordPtr lParam);
	WindowsApp(HINSTANCE__ *hInstance,const char *pGameName,MainWindowProc pCallBack=NULL,WordPtr uDefaultMemorySize=Burger::MemoryManagerHandle::DEFAULTMEMORYCHUNK,Word uDefaultHandleCount=Burger::MemoryManagerHandle::DEFAULTHANDLECOUNT,WordPtr uMinReserveSize=Burger::MemoryManagerHandle::DEFAULTMINIMUMRESERVE);
	~WindowsApp();
	BURGER_INLINE HINSTANCE__ *GetInstance(void) const { return m_hInstance; }
	BURGER_INLINE HWND__ *GetWindow(void) const { return m_hWindow; }
	BURGER_INLINE MainWindowProc GetCallBack(void) const { return m_pCallBack; }
	BURGER_INLINE void ResetWindowLocation(void) { m_bPreviousWindowXYValid = FALSE; }
	int BURGER_API InitWindow(const char *pGameName,MainWindowProc pCallBack);
	int BURGER_API SetWindowSize(Word uWidth,Word uHeight);
	void BURGER_API RecordWindowLocation(void);
	Word BURGER_API HandleCursor(Word uParam);
	void BURGER_API GetInputFocus(void);
	void BURGER_API KillInputFocus(void);
	static RunQueue::eReturnCode BURGER_API Poll(void *pSelf);
};
}
#endif
#if defined(BURGER_MACOSX) || defined(DOXYGEN)
namespace Burger {
class MacOSXApp : public GameApp {
	BURGER_DISABLECOPYCONSTRUCTORS(MacOSXApp);
	NSApplication *m_pApplication;			///< Pointer to the current application context (Copy of NSApp)
	NSApplicationDelegate *m_pApplicationDelegate;	///< Pointer to the current application delegate
	NSWindow *m_pWindow;					///< Game window
	Word m_bCenterWindow;					///< \ref TRUE if the window needs to be centered
	static RunQueue::eReturnCode BURGER_API EventPoll(void *pData);
public:
	MacOSXApp(WordPtr uDefaultMemorySize=Burger::MemoryManagerHandle::DEFAULTMEMORYCHUNK,Word uDefaultHandleCount=Burger::MemoryManagerHandle::DEFAULTHANDLECOUNT,WordPtr uMinReserveSize=Burger::MemoryManagerHandle::DEFAULTMINIMUMRESERVE);
	~MacOSXApp();
	void BURGER_API FocusWindow(void);
	Word BURGER_API SetWindowSize(Word uWidth,Word uHeight);
	BURGER_INLINE NSApplication *GetApplication(void) const { return m_pApplication; }
	BURGER_INLINE NSApplicationDelegate *GetDelegate(void) const { return m_pApplicationDelegate; }
	BURGER_INLINE NSWindow *GetWindow(void) const { return m_pWindow; }
};
}
#endif
#if defined(BURGER_IOS) || defined(DOXYGEN)
namespace Burger {
class iOSApp : public GameApp {
	UIWindow *m_pWindow;					///< Pointer to the UIWindow for the iOS application
	UIViewController *m_pViewController;	///< Pointer to the UIViewController to the window
	UIView *m_pView;						///< Pointer to the UIView being used
	BURGER_DISABLECOPYCONSTRUCTORS(iOSApp);
	static iOSApp *g_piOSApp;				///< Global singular application instance
public:
	iOSApp(WordPtr uDefaultMemorySize=Burger::MemoryManagerHandle::DEFAULTMEMORYCHUNK,Word uDefaultHandleCount=Burger::MemoryManagerHandle::DEFAULTHANDLECOUNT,WordPtr uMinReserveSize=Burger::MemoryManagerHandle::DEFAULTMINIMUMRESERVE);
	~iOSApp();
	int BURGER_API Run(void);
	BURGER_INLINE UIWindow *GetWindow(void) const { return m_pWindow; }
	UIWindow *BURGER_API CreateWindow(void);
	void BURGER_API ReleaseWindow(void);
	UIViewController *GetViewController(void) const { return m_pViewController; }
	UIView *GetView(void) const { return m_pView; }
	void BURGER_API SetViewController(UIViewController *pViewController,UIView *pView);
	BURGER_INLINE static iOSApp *GetApp(void) { return g_piOSApp; }
	static RunQueue::eReturnCode BURGER_API Poll(void *pSelf);
};
}
#endif
#if defined(BURGER_XBOX360) || defined(DOXYGEN)
namespace Burger {
class Xbox360App : public GameApp {
	BURGER_DISABLECOPYCONSTRUCTORS(Xbox360App);
public:
	Xbox360App(WordPtr uDefaultMemorySize=Burger::MemoryManagerHandle::DEFAULTMEMORYCHUNK,Word uDefaultHandleCount=Burger::MemoryManagerHandle::DEFAULTHANDLECOUNT,WordPtr uMinReserveSize=Burger::MemoryManagerHandle::DEFAULTMINIMUMRESERVE);
	~Xbox360App();
};
}
#endif
namespace Burger {
struct Dxt1Packet_t {
	Word16 m_uRGB565Color1;			///< First color endpoint in R5:G6:B5 little endian format
	Word16 m_uRGB565Color2;			///< Second color endpoint in R5:G6:B5 little endian format
	Word8 m_uColorIndexes[4];		///< 2 bits per pixel color indexes for 4x4 tile
	void Decompress(RGBAWord8_t *pOutput,WordPtr uStride = sizeof(RGBAWord8_t)*4) const;
	void Compress(const RGBAWord8_t *pInput,WordPtr uStride = sizeof(RGBAWord8_t)*4);
};
extern void BURGER_API DecompressImage(RGBAWord8_t *pOutput,WordPtr uOutputStride,Word uWidth,Word uHeight,const Dxt1Packet_t *pInput,WordPtr uInputStride);
}
namespace Burger {
struct Dxt3Packet_t {
	Word8 m_uAlpha[8];				///< Array of 4 bits per pixel alpha
	Word16 m_uRGB565Color1;			///< First color endpoint in R5:G6:B5 little endian format
	Word16 m_uRGB565Color2;			///< Second color endpoint in R5:G6:B5 little endian format
	Word8 m_uColorIndexes[4];		///< 2 bits per pixel color indexes for 4x4 tile
	void Decompress(RGBAWord8_t *pOutput,WordPtr uStride = sizeof(RGBAWord8_t)*4) const;
	void Compress(const RGBAWord8_t *pInput,WordPtr uStride = sizeof(RGBAWord8_t)*4);
};
extern void BURGER_API DecompressImage(RGBAWord8_t *pOutput,WordPtr uOutputStride,Word uWidth,Word uHeight,const Dxt3Packet_t *pInput,WordPtr uInputStride);
}
namespace Burger {
struct Dxt5Packet_t {
	Word8 m_uAlpha1;				///< First alpha endpoint in 8 bit intensity
	Word8 m_uAlpha2;				///< Second alpha endpoint in 8 bit intensity
	Word8 m_uAlphaIndexes[2][3];	///< Two 24 bit little endian values that contain 3 bits per pixel indexes for the 4x4 tile
	Word16 m_uRGB565Color1;			///< First color endpoint in R5:G6:B5 little endian format
	Word16 m_uRGB565Color2;			///< Second color endpoint in R5:G6:B5 little endian format
	Word8 m_uColorIndexes[4];		///< 2 bits per pixel color indexes for 4x4 tile
	void Decompress(RGBAWord8_t *pOutput,WordPtr uStride = sizeof(RGBAWord8_t)*4) const;
	void Compress(const RGBAWord8_t *pInput,WordPtr uStride = sizeof(RGBAWord8_t)*4);
};
extern void BURGER_API DecompressImage(RGBAWord8_t *pOutput,WordPtr uOutputStride,Word uWidth,Word uHeight,const Dxt5Packet_t *pInput,WordPtr uInputStride);
}
namespace Burger {
struct MACEState_t {
	Int32 m_iSample1;		///< Last running samples
	Int32 m_iSample2;		///< Second temp sample
	Int32 m_iLastStep;		///< Mask with 0x8000 for + or - direction
	Int32 m_iTableIndex;	///< Which slope table
	Int32 m_iLastAmplitude;	///< m_iLastSlope * m_iLastStep
	Int32 m_iLastSlope;		///< Last Slope value
};
extern void BURGER_API MACEExp1to6(const Word8 *pInput,Word8 *pOutput,WordPtr uPacketCount,MACEState_t *pInputState,MACEState_t *pOutputState,Word uNumChannels,Word uWhichChannel);
extern void BURGER_API MACEExp1to3(const Word8 *pInput,Word8 *pOutput,WordPtr uPacketCount,MACEState_t *pInputState,MACEState_t *pOutputState,Word uNumChannels,Word uWhichChannel);
}
namespace Burger {
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
class TextureDirectX9 : public Texture {
	BURGER_RTTI_IN_CLASS();
protected:
	IDirect3DTexture9 *m_pD3DTexture;
public:
	TextureDirectX9();
	TextureDirectX9(eWrapping uWrapping,eFilter uFilter);
	virtual ~TextureDirectX9();
	virtual Word Bind(Display *pDisplay);
	virtual void Release(Display *pDisplay);
	Word BURGER_API GetD3DFormat(void) const;
	BURGER_INLINE IDirect3DTexture9 * GetTexture(void) const { return m_pD3DTexture; }
};
#endif
}
namespace Burger {
#if defined(BURGER_WINDOWS)
class TextureOpenGL : public Texture {
	BURGER_RTTI_IN_CLASS();
protected:
	Word m_uTextureID;			///< OpenGL Texture ID
public:
	TextureOpenGL();
	TextureOpenGL(eWrapping uWrapping,eFilter uFilter);
	virtual ~TextureOpenGL();
	virtual Word Bind(Display *pDisplay);
	virtual void Release(Display *pDisplay);
	static int GetWrapping(eWrapping uWrapping);
	static int GetFilter(eFilter uFilter);
	BURGER_INLINE Word GetTextureID(void) const { return m_uTextureID; }
};
#endif
}
namespace Burger {
#if defined(BURGER_WINDOWS)
extern const Word8 g_pstexturedx9[];
extern const Word8 g_pstexturecolordx9[];
extern const Word8 g_vs20sprite2ddx9[];
extern const Word8 g_vsstaticpositiondx9[];
#endif
#if defined(BURGER_OPENGL_SUPPORTED)
extern const char g_glDiffuseTexture[];
extern const char g_glPosition[];
extern const char g_glTexcoord[];
extern const char g_glColor[];
extern const char g_glViewProjectionMatrix[];
extern const char g_glXYWidthHeight[];
extern const char g_pstexturegl[];
extern const char g_pstexturecolorgl[];
extern const char g_vs20sprite2dgl[];
extern const char g_vsstaticpositiongl[];
#endif
#if defined(BURGER_XBOX360)
extern const Word32 g_pstexture360[];
extern const Word32 g_pstexturecolor360[];
extern const Word32 g_vs20sprite2d360[];
extern const Word32 g_vsstaticposition360[];
#endif
#if defined(BURGER_VITA)
extern const Word8 g_pstexturevitaimage[];
extern const Word8 g_pstexturecolorvitaimage[];
extern const Word8 g_vs20sprite2dvitaimage[];
extern const Word8 g_vsstaticpositionvitaimage[];
#endif
}
namespace Burger {
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
class EffectDX9 : public Base {
	BURGER_RTTI_IN_CLASS();
protected:
	IDirect3DPixelShader9 *m_pPixelShader;		///< DirectX9 Pixel shader
	IDirect3DVertexShader9 *m_pVertexShader;	///< DirectX9 Vertex shader
	IDirect3DDevice9 *m_pDevice;				///< DirectX9 parent device
public:
	EffectDX9();
	virtual ~EffectDX9();
	void BURGER_API SetEffect(void);
};
#endif
class EffectOpenGL : public Base {
	BURGER_RTTI_IN_CLASS();
protected:
	Word m_uEffect;				///< Program ID for the compiled shader
public:
	EffectOpenGL();
	virtual ~EffectOpenGL();
	void BURGER_API SetEffect(void);
};
#if defined(BURGER_XBOX360) || defined(DOXYGEN)
class Effect : public Base {
	BURGER_RTTI_IN_CLASS();
protected:
	D3DPixelShader *m_pPixelShader;		///< (Xbox360 only) Pixel shader
	D3DVertexShader *m_pVertexShader;	///< (Xbox360 only) Vertex shader
	D3DDevice *m_pDevice;				///< (Xbox360 only) parent device
public:
	Effect();
	virtual ~Effect();
	void BURGER_API SetEffect(void);
};
#endif
#if defined(BURGER_WINDOWS)
typedef EffectDX9 Effect;
#elif defined(BURGER_OPENGL_SUPPORTED)
typedef EffectOpenGL Effect;
#endif
}
namespace Burger {
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
class EffectPositionTextureDX9 : public EffectDX9 {
	BURGER_RTTI_IN_CLASS();
public:
	EffectPositionTextureDX9(DisplayDirectX9 *pDisplay,const Word *pVertexMembers);
	void BURGER_API SetProjection(const Matrix4D_t *pMatrix);
};
#endif
#if defined(BURGER_OPENGL_SUPPORTED)
class EffectPositionTextureOpenGL : public EffectOpenGL {
	BURGER_RTTI_IN_CLASS();
protected:
	Int m_iEffectMatrix;		///< Index for the Matrix
public:
	EffectPositionTextureOpenGL(Display *pDisplay,const Word *pVertexMembers);
	void BURGER_API SetProjection(const Matrix4D_t *pMatrix);
};
#endif
#if defined(BURGER_XBOX360) || defined(DOXYGEN)
class EffectPositionTexture : public Effect {
	BURGER_RTTI_IN_CLASS();
public:
	EffectPositionTexture(Display *pDisplay,const Word *pVertexMembers);
	void BURGER_API SetProjection(const Matrix4D_t *pMatrix);
};
#endif
#if defined(BURGER_WINDOWS)
typedef EffectPositionTextureDX9 EffectPositionTexture;
#elif defined(BURGER_OPENGL_SUPPORTED)
typedef EffectPositionTextureOpenGL EffectPositionTexture;
#endif
}
namespace Burger {
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
class Effect2DDX9 : public EffectDX9 {
	BURGER_RTTI_IN_CLASS();
public:
	Effect2DDX9(DisplayDirectX9 *pDisplay,const Word *pVertexMembers);
	void BURGER_API SetPosition(float fX,float fY,float fWidth,float fHeight);
	void BURGER_API SetPosition(const Vector4D_t *pPosition);
};
#endif
#if defined(BURGER_OPENGL_SUPPORTED)
class Effect2DOpenGL : public EffectOpenGL {
	BURGER_RTTI_IN_CLASS();
protected:
	Int m_iEffect2DPosition;	///< Index for the position
public:
	Effect2DOpenGL(Display *pDisplay,const Word *pVertexMembers);
	void BURGER_API SetPosition(float fX,float fY,float fWidth,float fHeight);
	void BURGER_API SetPosition(const Vector4D_t *pPosition);
};
#endif
#if defined(BURGER_XBOX360) || defined(DOXYGEN)
class Effect2D : public Effect {
	BURGER_RTTI_IN_CLASS();
public:
	Effect2D(Display *pDisplay,const Word *pVertexMembers);
	void BURGER_API SetPosition(float fX,float fY,float fWidth,float fHeight);
	void BURGER_API SetPosition(const Vector4D_t *pPosition);
};
#endif
#if defined(BURGER_WINDOWS)
typedef Effect2DDX9 Effect2D;
#elif defined(BURGER_OPENGL_SUPPORTED)
typedef Effect2DOpenGL Effect2D;
#endif
}
namespace Burger {
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
class EffectPositionColorTextureDX9 : public EffectDX9 {
	BURGER_RTTI_IN_CLASS();
public:
	EffectPositionColorTextureDX9(DisplayDirectX9 *pDisplay,const Word *pVertexMembers);
	void BURGER_API SetProjection(const Matrix4D_t *pMatrix);
	void BURGER_API SetColor(const Vector4D_t *pColor);
};
#endif
#if defined(BURGER_OPENGL_SUPPORTED)
class EffectPositionColorTextureOpenGL : public EffectOpenGL {
	BURGER_RTTI_IN_CLASS();
protected:
	Int m_iEffectMatrix;		///< Index for the Matrix
	Int m_iEffectColor;			///< Index for the color adjustment
public:
	EffectPositionColorTextureOpenGL(Display *pDisplay,const Word *pVertexMembers);
	void BURGER_API SetProjection(const Matrix4D_t *pMatrix);
	void BURGER_API SetColor(const Vector4D_t *pColor);
};
#endif
#if defined(BURGER_XBOX360) || defined(DOXYGEN)
class EffectPositionColorTexture : public Effect {
	BURGER_RTTI_IN_CLASS();
public:
	EffectPositionColorTexture(Display *pDisplay,const Word *pVertexMembers);
	void BURGER_API SetProjection(const Matrix4D_t *pMatrix);
	void BURGER_API SetColor(const Vector4D_t *pColor);
};
#endif
#if defined(BURGER_WINDOWS)
typedef EffectPositionColorTextureDX9 EffectPositionColorTexture;
#elif defined(BURGER_OPENGL_SUPPORTED)
typedef EffectPositionColorTextureOpenGL EffectPositionColorTexture;
#endif
}
namespace Burger {
class FileBMP {
	Word16 m_uReserved1;			///< BMP Header reserved field #1
	Word16 m_uReserved2;			///< BMP Header reserved field #2
	Int32 m_iXPixelsPerMeter;		///< X Pixels per meter
	Int32 m_iYPixelsPerMeter;		///< Y Pixels per meter
	Word32 m_uColorsUsed;			///< Number of colors used
	Word32 m_uColorsImportant;		///< Number of important colors
	RGBAWord8_t m_Palette[256];		///< Palette found in the image
public:
	static void BURGER_API CompressRLE8(OutputMemoryStream *pOutput,const Word8 *pInput,WordPtr uInputLength,Word bSendEOP);
	static const char * BURGER_API DecompressRLE8(Word8 *pOutput,WordPtr uOutputLength,InputMemoryStream *pInput);
	enum {
		BMP_RGB=0,			///< Raw pixels
		BMP_RLE8=1,			///< 8 bit compression
		BMP_RLE4=2,			///< 4 bit compression
		BMP_BITFIELDS=3,	///< RGB bit field masks
		BMP_JPEG=4,			///< JPEG compression
		BMP_PNG=5,			///< PNG compression
		BMP_ALPHABITFIELDS=6,	///< RGBA bit field masks
		BMP_CMYK=11,		///< CMYK pixels
		BMP_CMYKRLE8=12,	///< 8 bit compression using a CMYK palette
		BMP_CMYKTLE4=13		///< 4 bit compression using a CMYK palette
	};
#if defined(BURGER_BIGENDIAN) || defined(DOXYGEN)
	static const Word32 FILETYPE = 0x424D5070;		///< 'BMPp' Mac File type for BMP files (Byte swapped on little endian machines)
	static const Word32 AUXTYPE = 0x6F676C65;		///< 'ogle' Mac creator code for BMP files (Byte swapped on little endian machines)
#else
	static const Word32 FILETYPE = 0x70504D42;		///< 'BMPp'
	static const Word32 AUXTYPE = 0x656C676F;		///< 'ogle'
#endif
	static const Int32 DEFAULT_PIXELS_PER_METER = 2835;	///< Default pixels per meter value for BMP files (2834.6472f)
	FileBMP();
	Word BURGER_API Load(Image *pOutput,InputMemoryStream *pInput);
	Word Save(OutputMemoryStream *pOutput,const Image *pImage,Word bCompression=FALSE);
	BURGER_INLINE Word16 GetReserved1(void) const { return m_uReserved1;}
	BURGER_INLINE void SetReserved1(Word16 uReserved1) { m_uReserved1 = uReserved1;}
	BURGER_INLINE Word16 GetReserved2(void) const { return m_uReserved2;}
	BURGER_INLINE void SetReserved2(Word16 uReserved2) { m_uReserved2 = uReserved2;}
	BURGER_INLINE Int32 GetXPixelsPerMeter(void) const { return m_iXPixelsPerMeter;}
	BURGER_INLINE void SetXPixelsPerMeter(Int32 iXPixelsPerMeter) { m_iXPixelsPerMeter = iXPixelsPerMeter;}
	BURGER_INLINE Int32 GetYPixelsPerMeter(void) const { return m_iYPixelsPerMeter;}
	BURGER_INLINE void SetYPixelsPerMeter(Int32 iYPixelsPerMeter) { m_iYPixelsPerMeter = iYPixelsPerMeter;}
	BURGER_INLINE const RGBAWord8_t *GetPalette(void) const { return m_Palette; }
	BURGER_INLINE RGBAWord8_t *GetPalette(void) { return m_Palette; }
	void SetPalette(const RGBWord8_t *pPalette,Word uStartIndex=0,Word uPaletteSize=256);
	void SetPalette(const RGBAWord8_t *pPalette,Word uStartIndex=0,Word uPaletteSize=256);
};
}
namespace Burger {
class FileDDS {
	Word32 m_uReserved[11];
public:
#if defined(BURGER_BIGENDIAN) || defined(DOXYGEN)
	static const Word32 FILETYPE = 0x44445320;		///< 'DDS ' Mac File type for DDS files (Byte swapped on little endian machines)
	static const Word32 AUXTYPE = 0x474B4F4E;		///< 'GKON' Mac creator code for DDS files (Byte swapped on little endian machines)
#else
	static const Word32 FILETYPE = 0x20534444;		///< 'DDS '
	static const Word32 AUXTYPE = 0x4E4F4B47;		///< 'GKON'
#endif
	FileDDS();
	Image *Load(InputMemoryStream *pInput);
	Word Save(OutputMemoryStream *pOutput,const Image *pImage);
	BURGER_INLINE const Word32 *GetReserved(void) const { return m_uReserved; }
	BURGER_INLINE Word32 *GetReserved(void) { return m_uReserved; }
};
}
namespace Burger {
class FileGIF {
	Word8 m_bAspectRatio;			///< GIF aspect ratio
	RGBAWord8_t m_Palette[256];		///< Palette found in the image
public:
	struct GIFDecoder {
		InputMemoryStream *m_pInput;	///< Pointer to packed data
		Word m_uBitBucket;				///< Current bit bucket
		Word m_uBitCount;				///< Current valid bit count in bucket
		Word m_uChunkCount;				///< Number of bytes in stream
		Word m_uLZWCodeSize;			///< Starting data size
		const Word8 *m_LZWTable[4096];	///< Dictionary pointers
		Word8 m_LZWArray[256]; 			///< 0-255 for default data
		Word m_LZWSize[4096]; 			///< Size of each entry
		void Init(void);
		void Reset(void);
		Word GetCode(Word uBitsRequested);
	};
	static void BURGER_API DiscardExtension(InputMemoryStream *pInput);
	static const char *BURGER_API UnpackGIFLZW(Word8 *pOutput,WordPtr uOutputLength,InputMemoryStream *pInput);
#if defined(BURGER_BIGENDIAN) || defined(DOXYGEN)
	static const Word32 FILETYPE = 0x47494666;		///< 'GIFf' Mac File type for GIF files (Byte swapped on little endian machines)
	static const Word32 AUXTYPE = 0x6F676C65;		///< 'ogle' Mac creator code for GIF files (Byte swapped on little endian machines)
#else
	static const Word32 FILETYPE = 0x66464947;		///< 'GIFf'
	static const Word32 AUXTYPE = 0x656C676F;		///< 'ogle'
#endif
	FileGIF();
	Image *Load(InputMemoryStream *pInput);
	BURGER_INLINE Word GetAspectRatio(void) const { return m_bAspectRatio;}
	BURGER_INLINE void SetAspectRatio(Word bAspectRatio) { m_bAspectRatio = static_cast<Word8>(bAspectRatio);}
	BURGER_INLINE const RGBAWord8_t *GetPalette(void) const { return m_Palette; }
	BURGER_INLINE RGBAWord8_t *GetPalette(void) { return m_Palette; }
	void SetPalette(const RGBWord8_t *pPalette,Word uStartIndex=0,Word uPaletteSize=256);
	void SetPalette(const RGBAWord8_t *pPalette,Word uStartIndex=0,Word uPaletteSize=256);
};
}
namespace Burger {
class FileINI {
public:
	class Generic : public Base {
	public:
		enum eType {
			LINEENTRY_ROOT,			///< Only used for root objects.
			LINEENTRY_SECTION,		///< INI section header
			LINEENTRY_ENTRY,		///< Data entries attached to a section
			LINEENTRY_COMMENT		///< "Comment" strings to retain user supplied information
		};
	private:
		LinkedListPointer m_Link;	///< Linked list entry
		eType m_eType; 				///< Type of derived class
	public:
		Generic(eType uType);
		virtual ~Generic();
		BURGER_INLINE Generic *GetNext(void) const { return static_cast<Generic *>(m_Link.GetNext()->GetData()); }
		BURGER_INLINE Generic *GetPrevious(void) const { return static_cast<Generic *>(m_Link.GetPrevious()->GetData()); }
		BURGER_INLINE eType GetType(void) const { return m_eType; }
		BURGER_INLINE void InsertBefore(Generic *pGeneric) { m_Link.InsertBefore(&pGeneric->m_Link); }
		BURGER_INLINE void InsertAfter(Generic *pGeneric) { m_Link.InsertAfter(&pGeneric->m_Link); }
	};
	class Comment : public Generic  {
		String m_Comment;	///< Unmodified text for a comment line
	public:
		Comment();
		Comment(const char *pComment);
		virtual ~Comment();
		BURGER_INLINE const char *GetText(void) const { return m_Comment.GetPtr(); }
		BURGER_INLINE void SetText(const char *pInput) { m_Comment.Set(pInput); }
		BURGER_INLINE void SetText(const String *pInput) { m_Comment = pInput[0]; }
	};
	class Entry : public Generic {
		String m_Key;	   		///< Value's key
		String m_Value;			///< UTF-8 form of the value
	public:
		Entry();
		Entry(const char *pKey,const char *pValue);
		virtual ~Entry();
		BURGER_INLINE const char *GetKey(void) const { return m_Key.GetPtr(); }
		BURGER_INLINE void SetKey(const char *pInput) { m_Key.Set(pInput); }
		BURGER_INLINE void SetKey(const String *pInput) { m_Key = pInput[0]; }
		BURGER_INLINE const char *GetValue(void) const { return m_Value.GetPtr(); }
		BURGER_INLINE void SetValue(const char *pInput) { m_Value.Set(pInput); }
		BURGER_INLINE void SetValue(const String *pInput) { m_Value = pInput[0]; }
		Word GetBoolean(Word bDefault) const;
		void SetBoolean(Word bValue);
		Word GetWord(Word uDefault,Word uMin=0,Word uMax=BURGER_MAXUINT) const;
		void SetWord(Word uValue);
		void SetWordHex(Word uValue);
		Int GetInt(Int iDefault,Int iMin=(-BURGER_MAXINT)-1,Int iMax=BURGER_MAXINT) const;
		void SetInt(Int iValue);
		float GetFloat(float fDefault,float fMin,float fMax) const;
		void SetFloat(float fValue);
		double GetDouble(double dDefault,double dMin,double dMax) const;
		void SetDouble(double fValue);
		void GetString(String *pOutput,const char *pDefault) const;
		void SetString(const char *pValue);
	};
	class Section : public Generic  {
		Generic m_Root;			///< Linked list root for all attached entries
		String m_SectionName;	///< Name of the section
	public:
		Section();
		Section(const char *pSection);
		virtual ~Section();
		Word Save(OutputMemoryStream *pOutput) const;
		BURGER_INLINE const char *GetName(void) const { return m_SectionName.GetPtr(); }
		BURGER_INLINE void SetName(const char *pInput) { m_SectionName.Set(pInput); }
		BURGER_INLINE void SetName(const String *pInput) { m_SectionName = pInput[0]; }
		Entry *AddEntry(const char *pKey,const char *pValue);
		Entry *FindEntry(const char *pKey) const;
		Entry *FindEntry(const char *pKey,Word bAlwaysCreate);
		Comment *AddComment(const char *pComment);
		const char *GetValue(const char *pKey) const;
		void SetValue(const char *pKey,const char *pInput);
		void SetValue(const char *pKey,const String *pInput);
		Word GetBoolean(const char *pKey,Word bDefault) const;
		void SetBoolean(const char *pKey,Word bValue);
		Word GetWord(const char *pKey,Word uDefault,Word uMin=0,Word uMax=BURGER_MAXUINT) const;
		void SetWord(const char *pKey,Word uValue);
		void SetWordHex(const char *pKey,Word uValue);
		Int GetInt(const char *pKey,Int iDefault,Int iMin=(-BURGER_MAXINT)-1,Int iMax=BURGER_MAXINT) const;
		void SetInt(const char *pKey,Int iValue);
		float GetFloat(const char *pKey,float fDefault,float fMin,float fMax) const;
		void SetFloat(const char *pKey,float fValue);
		double GetDouble(const char *pKey,double dDefault,double dMin,double dMax) const;
		void SetDouble(const char *pKey,double dValue);
		void GetString(String *pOutput,const char *pKey,const char *pDefault) const;
		void SetString(const char *pKey,const char *pValue);
	};
private:
	Generic m_Root;				///< Root entry for a list of sections
public:
	FileINI();
	~FileINI();
	static FileINI * BURGER_API New(void);
	static FileINI * BURGER_API New(const char *pFilename,Word bAlwaysCreate=FALSE);
	static FileINI * BURGER_API New(Filename *pFilename,Word bAlwaysCreate=FALSE);
	static FileINI * BURGER_API New(InputMemoryStream *pInput,Word bAlwaysCreate=FALSE);
	Word Init(const char *pFilename);
	Word Init(Filename *pFilename);
	Word Init(InputMemoryStream *pInput);
	void Shutdown(void);
	Word Save(OutputMemoryStream *pOutput) const;
	Section *AddSection(const char *pSectionName);
	Section *FindSection(const char *pSectionName,Word bAlwaysCreate=FALSE);
	void DeleteSection(const char *pSectionName);
};
}
namespace Burger {
class FileLBM {
	RGBAWord8_t m_Palette[256];		///< Palette found in the image
public:
	static const char * BURGER_API UnpackILBMData(Word8 *pOutput,WordPtr uOutputLength,InputMemoryStream *pInput);
	static const char * BURGER_API UnpackILBM(Word8 *pOutput,Word uWidth,Word uHeight,Word uDepth,InputMemoryStream *pInput);
	static const char * BURGER_API SeekIffChunk(InputMemoryStream *pInput,Word32 uID,WordPtr uStartOffset);
#if defined(BURGER_BIGENDIAN) || defined(DOXYGEN)
	static const Word32 FILETYPE = 0x494C424D;		///< 'ILBM' Mac File type for LBM files (Byte swapped on little endian machines)
	static const Word32 AUXTYPE = 0x6F676C65;		///< 'ogle' Mac creator code for LBM files (Byte swapped on little endian machines)
#else
	static const Word32 FILETYPE = 0x4D424C49;		///< 'ILBM'
	static const Word32 AUXTYPE = 0x656C676F;		///< 'ogle'
#endif
	FileLBM();
	Image *Load(InputMemoryStream *pInput);
	BURGER_INLINE const RGBAWord8_t *GetPalette(void) const { return m_Palette; }
	BURGER_INLINE RGBAWord8_t *GetPalette(void) { return m_Palette; }
	void SetPalette(const RGBWord8_t *pPalette,Word uStartIndex=0,Word uPaletteSize=256);
	void SetPalette(const RGBAWord8_t *pPalette,Word uStartIndex=0,Word uPaletteSize=256);
};
}
namespace Burger {
class FilePCX {
	Word16 m_uXPixelsPerInch;		///< X Pixels per inch (72)
	Word16 m_uYPixelsPerInch;		///< Y Pixels per inch (72)
	RGBAWord8_t m_Palette[256];		///< Palette found in the image
	Word8 m_EGAPalette[48];			///< EGA palette
public:
	static const char * BURGER_API DecompressPCX(Word8 *pOutput,WordPtr uOutputLength,InputMemoryStream *pInput);
	static void BURGER_API Merge3Planes(Word8 *pOutput,const Word8 *pInput,WordPtr uWidth);
	enum {
		PCX_VERSION25=0,	///< File version 2.5
		PCX_VERSION28=2,	///< File version 2.8
		PCX_VERSION28COLOR=3,	///< File version 2.8 with true color support
		PCX_VERSION30=5		///< File version 3.0
	};
#if defined(BURGER_BIGENDIAN) || defined(DOXYGEN)
	static const Word32 FILETYPE = 0x50435878;		///< 'PCXx' Mac File type for PCX files (Byte swapped on little endian machines)
	static const Word32 AUXTYPE = 0x474B4F4E;		///< 'GKON' Mac creator code for PCX files (Byte swapped on little endian machines)
#else
	static const Word32 FILETYPE = 0x78584350;		///< 'PCXx'
	static const Word32 AUXTYPE = 0x4E4F4B47;		///< 'GKON'
#endif
	static const Word16 DEFAULT_PIXELS_PER_INCH = 72;	///< Default pixels per inch value for PCX files
	FilePCX();
	Image *Load(InputMemoryStream *pInput);
	BURGER_INLINE Int32 GetXPixelsPerInch(void) const { return m_uXPixelsPerInch;}
	BURGER_INLINE void SetXPixelsPerInch(Word16 uXPixelsPerInch) { m_uXPixelsPerInch = uXPixelsPerInch;}
	BURGER_INLINE Int32 GetYPixelsPerInch(void) const { return m_uYPixelsPerInch;}
	BURGER_INLINE void SetYPixelsPerInch(Word16 uYPixelsPerInch) { m_uYPixelsPerInch = uYPixelsPerInch;}
	BURGER_INLINE const RGBAWord8_t *GetPalette(void) const { return m_Palette; }
	BURGER_INLINE RGBAWord8_t *GetPalette(void) { return m_Palette; }
	BURGER_INLINE const Word8 *GetEGAPalette(void) const { return m_EGAPalette; }
	BURGER_INLINE Word8 *GetEGAPalette(void) { return m_EGAPalette; }
	void SetPalette(const RGBWord8_t *pPalette,Word uStartIndex=0,Word uPaletteSize=256);
	void SetPalette(const RGBAWord8_t *pPalette,Word uStartIndex=0,Word uPaletteSize=256);
};
}
namespace Burger {
class FilePNG {
	RGBAWord8_t m_Palette[256];		///< Palette found in the image
	WordPtr m_uStartOffset;			///< PNG file image chunk start offset
	WordPtr m_uNextOffset;			///< Offset to the next chunk
	Word32 m_uChunkSize;			///< Size of the current chunk in bytes
	Word32 m_uPNGID;				///< Untouched ID of the current PNG chunk
protected:
	const char * BURGER_API SeekChunk(InputMemoryStream *pInput,Word32 uID,WordPtr uStartOffset);
public:
	enum {
		PNG_GREYSCALE=0,		///< Each pixel is a grayscale sample.
		PNG_RGB=2,				///< Each pixel is an R,G,B triple.
		PNG_INDEXED=3,			///< Each pixel is a palette index;
		PNG_GREYSCALEALPHA=4,	///< Each pixel is a grayscale sample,
		PNG_RGBA=6				///< Each pixel is an R,G,B,A quad,
	};
	const char * BURGER_API SeekPNGChunk(InputMemoryStream *pInput,Word32 uID);
	const char * BURGER_API SeekNextPNGChunk(InputMemoryStream *pInput,Word32 uID);
#if defined(BURGER_BIGENDIAN) || defined(DOXYGEN)
	static const Word32 FILETYPE = 0x504E4720;		///< 'PNG ' Mac File type for PNG files (Byte swapped on little endian machines)
	static const Word32 AUXTYPE = 0x6F676C65;		///< 'ogle' Mac creator code for PNG files (Byte swapped on little endian machines)
#else
	static const Word32 FILETYPE = 0x20474E50;		///< 'PNG '
	static const Word32 AUXTYPE = 0x656C676F;		///< 'ogle'
#endif
	FilePNG();
	Word BURGER_API Load(Image *pOutput,InputMemoryStream *pInput);
	BURGER_INLINE const RGBAWord8_t *GetPalette(void) const { return m_Palette; }
	BURGER_INLINE RGBAWord8_t *GetPalette(void) { return m_Palette; }
	void SetPalette(const RGBWord8_t *pPalette,Word uStartIndex=0,Word uPaletteSize=256);
	void SetPalette(const RGBAWord8_t *pPalette,Word uStartIndex=0,Word uPaletteSize=256);
};
}
namespace Burger {
class FileTGA {
	RGBAWord8_t m_Palette[256];		///< Palette found in the image
public:
	static void BURGER_API UnpackPixel8(Word8 *pOutput,WordPtr uOutputLength,InputMemoryStream *pInput);
	static void BURGER_API UnpackPixel16(Word8 *pOutput,WordPtr uOutputLength,InputMemoryStream *pInput);
	static void BURGER_API UnpackPixel24(Word8 *pOutput,WordPtr uOutputLength,InputMemoryStream *pInput);
	static void BURGER_API UnpackPixel32(Word8 *pOutput,WordPtr uOutputLength,InputMemoryStream *pInput);
	enum {
		TGA_NOIMAGE=0,		///< Palette only
		TGA_RGBINDEXED=1,	///< 8 bit uncompressed
		TGA_RGB=2,			///< RGB uncompressed
		TGA_GRAY=3,			///< Grayscale uncompressed
		TGA_RLEINDEXED=9,	///< 8 bit compressed
		TGA_RLERGB=10,		///< RGB compressed
		TGA_RLEGRAY=11		///< Grayscale compressed
	};
#if defined(BURGER_BIGENDIAN) || defined(DOXYGEN)
	static const Word32 FILETYPE = 0x54504943;		///< 'TPIC' Mac File type for TGA files (Byte swapped on little endian machines)
	static const Word32 AUXTYPE = 0x474B4F4E;		///< 'GKON' Mac creator code for TGA files (Byte swapped on little endian machines)
#else
	static const Word32 FILETYPE = 0x43495054;		///< 'TPIC'
	static const Word32 AUXTYPE = 0x4E4F4B47;		///< 'GKON'
#endif
	Word BURGER_API Load(Image *pOutput,InputMemoryStream *pInput);
	BURGER_INLINE const RGBAWord8_t *GetPalette(void) const { return m_Palette; }
	BURGER_INLINE RGBAWord8_t *GetPalette(void) { return m_Palette; }
	void SetPalette(const RGBWord8_t *pPalette,Word uStartIndex=0,Word uPaletteSize=256);
	void SetPalette(const RGBAWord8_t *pPalette,Word uStartIndex=0,Word uPaletteSize=256);
};
}
namespace Burger {
class FileXML {
public:
	class Element;
	class Attribute;
	class RawText;
	class Generic : public Base {
	public:
		enum eType {
			XML_ROOT,			///< Only used for root objects.
			XML_COMMENT,		///< "Comment" strings to retain user supplied information
			XML_CDATA,			///< "CDATA" strings of data that is ignored by the parser
			XML_ATTRIBUTE,		///< Attribute attached to a tag
			XML_DECLARATION,	///< XML declaration
			XML_DOCUMENT,		///< Document header (DTD)
			XML_ELEMENT,		///< Data entries attached to a document header
			XML_TEXT,			///< Text content attached to a document
			XML_UNKNOWN			///< Unknown XML entry
		};
	private:
		LinkedListPointer m_Link;	///< Linked list entry
		eType m_eType; 				///< Type of derived class
	public:
		Generic(eType uType);
		virtual ~Generic();
		virtual Word Parse(InputMemoryStream *pInput);
		virtual Word Save(OutputMemoryStream *pOutput,Word uDepth) const;
		BURGER_INLINE Generic *GetNext(void) const { return static_cast<Generic *>(m_Link.GetNext()->GetData()); }
		BURGER_INLINE Generic *GetPrevious(void) const { return static_cast<Generic *>(m_Link.GetPrevious()->GetData()); }
		BURGER_INLINE eType GetType(void) const { return m_eType; }
		BURGER_INLINE void InsertBefore(Generic *pGeneric) { m_Link.InsertBefore(&pGeneric->m_Link); }
		BURGER_INLINE void InsertAfter(Generic *pGeneric) { m_Link.InsertAfter(&pGeneric->m_Link); }
		Element * BURGER_API GetNextElement(void) const;
		Element * BURGER_API GetNextElement(const char *pElementName) const;
		Generic * BURGER_API GetNextItem(void) const;
	};
	class Root : public Generic {
	public:
		Root();
		virtual ~Root();
		Word BURGER_API ParseList(InputMemoryStream *pInput,Word bAllowRawText=FALSE);
		Word BURGER_API SaveList(OutputMemoryStream *pOutput,Word uDepth) const;
		void BURGER_API DeleteList(void);
		Generic * BURGER_API FindType(eType uType) const;
		void BURGER_API DeleteType(eType uType);
		const Element * BURGER_API FindElement(const char *pElementName) const;
		Element * BURGER_API FindElement(const char *pElementName,Word bAlwaysCreate=FALSE);
		Element * BURGER_API AddElement(const char *pElementName);
		void BURGER_API DeleteElement(const char *pElementName);
		void BURGER_API DeleteElements(const char *pElementName);
		const Attribute * BURGER_API FindAttribute(const char *pAttributeName) const;
		Attribute * BURGER_API FindAttribute(const char *pAttributeName,Word bAlwaysCreate=FALSE);
		Attribute * BURGER_API AddAttribute(const char *pAttributeName,const char *pValue=NULL);
		void BURGER_API DeleteAttribute(const char *pAttributeName);
		const RawText * BURGER_API FindRawText(void) const;
		RawText * BURGER_API FindRawText(Word bAlwaysCreate=FALSE);
		RawText * BURGER_API AddRawText(const char *pValue=NULL);
		void BURGER_API DeleteRawText(void);
	};
	class Comment : public Generic  {
		String m_Comment;	///< Unmodified text for a comment line
	public:
		Comment();
		Comment(const char *pComment);
		virtual ~Comment();
		virtual Word Parse(InputMemoryStream *pInput);
		virtual Word Save(OutputMemoryStream *pOutput,Word uDepth) const;
		BURGER_INLINE const char *GetText(void) const { return m_Comment.GetPtr(); }
		BURGER_INLINE void SetText(const char *pInput) { m_Comment.Set(pInput); }
		BURGER_INLINE void SetText(const String *pInput) { m_Comment = pInput[0]; }
		static Comment * BURGER_API New(InputMemoryStream *pInput);
		static Comment * BURGER_API New(const char *pComment);
	};
	class CData : public Generic  {
		String m_CData;				///< Unmodified text for a CData line
	public:
		CData();
		CData(const char *pCData);
		virtual ~CData();
		virtual Word Parse(InputMemoryStream *pInput);
		virtual Word Save(OutputMemoryStream *pOutput,Word uDepth) const;
		BURGER_INLINE const char *GetText(void) const { return m_CData.GetPtr(); }
		BURGER_INLINE void SetText(const char *pInput) { m_CData.Set(pInput); }
		BURGER_INLINE void SetText(const String *pInput) { m_CData = pInput[0]; }
		static CData * BURGER_API New(InputMemoryStream *pInput);
		static CData * BURGER_API New(const char *pCData);
	};
	class Attribute : public Generic {
		String m_Key;				///< Attribute keyword
		String m_Value;				///< Value attached to the attribute
	public:
		Attribute();
		virtual ~Attribute();
		virtual Word Parse(InputMemoryStream *pInput);
		virtual Word Save(OutputMemoryStream *pOutput,Word uDepth) const;
		BURGER_INLINE const char *GetKey(void) const { return m_Key.GetPtr(); }
		BURGER_INLINE void SetKey(const char *pInput) { m_Key.Set(pInput); }
		BURGER_INLINE void SetKey(const String *pInput) { m_Key = pInput[0]; }
		BURGER_INLINE const char *GetValue(void) const { return m_Value.GetPtr(); }
		BURGER_INLINE void SetValue(const char *pInput) { m_Value.Set(pInput); }
		BURGER_INLINE void SetValue(const String *pInput) { m_Value = pInput[0]; }
		BURGER_INLINE Word GetBoolean(Word bDefault) const { return m_Value.GetBoolean(bDefault); }
		BURGER_INLINE void SetBoolean(Word bValue) { m_Value.SetYesNo(bValue); }
		BURGER_INLINE Word GetWord(Word uDefault,Word uMin=0,Word uMax=BURGER_MAXUINT) const { return m_Value.GetWord(uDefault,uMin,uMax); }
		BURGER_INLINE void SetWord(Word uValue) { m_Value.SetWord(uValue); }
		BURGER_INLINE void SetWordHex(Word uValue) { m_Value.SetWordHex(uValue); }
		BURGER_INLINE Int GetInt(Int iDefault,Int iMin=(-BURGER_MAXINT)-1,Int iMax=BURGER_MAXINT) const { return m_Value.GetInt(iDefault,iMin,iMax); }
		BURGER_INLINE void SetInt(Int iValue) { m_Value.SetInt(iValue); }
		BURGER_INLINE float GetFloat(float fDefault) const { return m_Value.GetFloat(fDefault); }
		BURGER_INLINE float GetFloat(float fDefault,float fMin,float fMax) const { return m_Value.GetFloat(fDefault,fMin,fMax); }
		BURGER_INLINE void SetFloat(float fValue) { m_Value.SetFloat(fValue); }
		BURGER_INLINE double GetDouble(double dDefault) const { return m_Value.GetDouble(dDefault); }
		BURGER_INLINE double GetDouble(double dDefault,double dMin,double dMax) const { return m_Value.GetDouble(dDefault,dMin,dMax); }
		BURGER_INLINE void SetDouble(double dValue) { m_Value.SetDouble(dValue); }
		static Attribute * BURGER_API New(InputMemoryStream *pInput);
		static Attribute * BURGER_API New(const char *pInput,const char *pValue=NULL);
		Attribute * BURGER_API Update(Root *pRoot,const char *pKey,const char *pValue);
	};
	class Declaration : public Generic {
		String m_Encoding;		///< ASCII of the encoding (Normally it's UTF-8)
		float m_fVersion;		///< Version number of the declaration
		Word m_bStandalone;		///< \ref TRUE if it's a standalone XML file
	public:
		Declaration();
		Declaration(float fVersion,const char *pEncoding=NULL,Word bStandalone=2);
		virtual ~Declaration();
		virtual Word Parse(InputMemoryStream *pInput);
		virtual Word Save(OutputMemoryStream *pOutput,Word uDepth) const;
		BURGER_INLINE float GetVersion(void) const { return m_fVersion; }
		void BURGER_API SetVersion(float fInput=1.0f);
		BURGER_INLINE const char *GetEncoding(void) const { return m_Encoding.GetPtr(); }
		BURGER_INLINE void SetEncoding(const char *pInput) { m_Encoding.Set(pInput); }
		BURGER_INLINE void SetEncoding(const String *pInput) { m_Encoding = pInput[0]; }
		Word BURGER_INLINE GetStandalone(void) const { return m_bStandalone==1;}
		void BURGER_INLINE SetStandalone(Word bInput) { m_bStandalone = bInput; }
		static Declaration * BURGER_API New(InputMemoryStream *pInput);
		static Declaration * BURGER_API New(float fVersion,const char *pEncoding=NULL,Word bStandalone=2);
	};
	class RawText : public Generic {
		String m_Text;			///< Name of the element
	public:
		RawText();
		RawText(const char *pText);
		virtual ~RawText();
		virtual Word Parse(InputMemoryStream *pInput);
		virtual Word Save(OutputMemoryStream *pOutput,Word uDepth) const;
		BURGER_INLINE const char *GetText(void) const { return m_Text.GetPtr(); }
		BURGER_INLINE void SetText(const char *pInput) { m_Text.Set(pInput); }
		BURGER_INLINE void SetText(const String *pInput) { m_Text = pInput[0]; }
		BURGER_INLINE Word GetBoolean(Word bDefault) const { return m_Text.GetBoolean(bDefault); }
		BURGER_INLINE void SetBoolean(Word bValue) { m_Text.SetYesNo(bValue); }
		BURGER_INLINE Word GetWord(Word uDefault,Word uMin=0,Word uMax=BURGER_MAXUINT) const { return m_Text.GetWord(uDefault,uMin,uMax); }
		BURGER_INLINE void SetWord(Word uValue) { m_Text.SetWord(uValue); }
		BURGER_INLINE void SetWordHex(Word uValue) { m_Text.SetWordHex(uValue); }
		BURGER_INLINE Int GetInt(Int iDefault,Int iMin=(-BURGER_MAXINT)-1,Int iMax=BURGER_MAXINT) const { return m_Text.GetInt(iDefault,iMin,iMax); }
		BURGER_INLINE void SetInt(Int iValue) { m_Text.SetInt(iValue); }
		BURGER_INLINE float GetFloat(float fDefault) const { return m_Text.GetFloat(fDefault); }
		BURGER_INLINE float GetFloat(float fDefault,float fMin,float fMax) const { return m_Text.GetFloat(fDefault,fMin,fMax); }
		BURGER_INLINE void SetFloat(float fValue) { m_Text.SetFloat(fValue); }
		BURGER_INLINE double GetDouble(double dDefault) const { return m_Text.GetDouble(dDefault); }
		BURGER_INLINE double GetDouble(double dDefault,double dMin,double dMax) const { return m_Text.GetDouble(dDefault,dMin,dMax); }
		BURGER_INLINE void SetDouble(double dValue) { m_Text.SetDouble(dValue); }
		static RawText * BURGER_API New(InputMemoryStream *pInput);
		static RawText * BURGER_API New(const char *pText);
	};
	class Element : public Generic {
		Root m_Attributes;	///< Linked list root for all attached attributes
		Root m_Root;		///< Linked list root for all contained objects
		String m_Name;		///< Name of the element
	public:
		Element();
		Element(const char *pName);
		virtual ~Element();
		virtual Word Parse(InputMemoryStream *pInput);
		virtual Word Save(OutputMemoryStream *pOutput,Word uDepth) const;
		BURGER_INLINE Root * GetRoot(void) { return &m_Root; }
		BURGER_INLINE const Root * GetRoot(void) const { return &m_Root; }
		BURGER_INLINE const Element * FindElement(const char *pElementName) const { return m_Root.FindElement(pElementName); }
		BURGER_INLINE Element * FindElement(const char *pElementName,Word bAlwaysCreate=FALSE) { return m_Root.FindElement(pElementName,bAlwaysCreate); }
		BURGER_INLINE Element * AddElement(const char *pElementName) { return m_Root.AddElement(pElementName); }
		BURGER_INLINE void DeleteElement(const char *pElementName) { return m_Root.DeleteElement(pElementName); }
		BURGER_INLINE void DeleteElements(const char *pElementName) { return m_Root.DeleteElements(pElementName); }
		BURGER_INLINE Attribute * FindAttribute(const char *pAttributeName,Word bAlwaysCreate=FALSE) { return m_Attributes.FindAttribute(pAttributeName,bAlwaysCreate); }
		BURGER_INLINE Attribute * AddAttribute(const char *pAttributeName,const char *pValue=NULL) { return m_Attributes.AddAttribute(pAttributeName,pValue); }
		BURGER_INLINE void DeleteAttribute(const char *pAttributeName) { return m_Attributes.DeleteAttribute(pAttributeName); }
		BURGER_INLINE const char *GetName(void) const { return m_Name.GetPtr(); }
		BURGER_INLINE void SetName(const char *pInput) { m_Name.Set(pInput); }
		BURGER_INLINE void SetName(const String *pInput) { m_Name = pInput[0]; }
		Word BURGER_API GetBoolean(Word bDefault) const;
		void BURGER_API SetBoolean(Word bValue);
		Word BURGER_API GetWord(Word uDefault,Word uMin=0,Word uMax=BURGER_MAXUINT) const;
		void BURGER_API SetWord(Word uValue);
		void BURGER_API SetWordHex(Word uValue);
		Int BURGER_API GetInt(Int iDefault,Int iMin=(-BURGER_MAXINT)-1,Int iMax=BURGER_MAXINT) const;
		void BURGER_API SetInt(Int iValue);
		float BURGER_API GetFloat(float fDefault) const;
		float BURGER_API GetFloat(float fDefault,float fMin,float fMax) const;
		void BURGER_API SetFloat(float fValue);
		double BURGER_API GetDouble(double dDefault) const;
		double BURGER_API GetDouble(double dDefault,double dMin,double dMax) const;
		void BURGER_API SetDouble(double dValue);
		const char *BURGER_API GetString(const char *pDefault) const;
		void BURGER_API SetString(const char *pValue);
		Word BURGER_API AttributeGetBoolean(const char *pAttributeName,Word bDefault) const;
		void BURGER_API AttributeSetBoolean(const char *pAttributeName,Word bValue);
		Word BURGER_API AttributeGetWord(const char *pAttributeName,Word uDefault,Word uMin=0,Word uMax=BURGER_MAXUINT) const;
		void BURGER_API AttributeSetWord(const char *pAttributeName,Word uValue);
		void BURGER_API AttributeSetWordHex(const char *pAttributeName,Word uValue);
		Int BURGER_API AttributeGetInt(const char *pAttributeName,Int iDefault,Int iMin=(-BURGER_MAXINT)-1,Int iMax=BURGER_MAXINT) const;
		void BURGER_API AttributeSetInt(const char *pAttributeName,Int iValue);
		float BURGER_API AttributeGetFloat(const char *pAttributeName,float fDefault) const;
		float BURGER_API AttributeGetFloat(const char *pAttributeName,float fDefault,float fMin,float fMax) const;
		void BURGER_API AttributeSetFloat(const char *pAttributeName,float fValue);
		double BURGER_API AttributeGetDouble(const char *pAttributeName,double dDefault) const;
		double BURGER_API AttributeGetDouble(const char *pAttributeName,double dDefault,double dMin,double dMax) const;
		void BURGER_API AttributeSetDouble(const char *pAttributeName,double dValue);
		const char *BURGER_API AttributeGetString(const char *pAttributeName,const char *pDefault) const;
		void BURGER_API AttributeSetString(const char *pAttributeName,const char *pValue);
		Word BURGER_API ElementGetBoolean(const char *pElementName,Word bDefault) const;
		void BURGER_API ElementSetBoolean(const char *pElementName,Word bValue);
		Word BURGER_API ElementGetWord(const char *pElementName,Word uDefault,Word uMin=0,Word uMax=BURGER_MAXUINT) const;
		void BURGER_API ElementSetWord(const char *pElementName,Word uValue);
		void BURGER_API ElementSetWordHex(const char *pElementName,Word uValue);
		Int BURGER_API ElementGetInt(const char *pElementName,Int iDefault,Int iMin=(-BURGER_MAXINT)-1,Int iMax=BURGER_MAXINT) const;
		void BURGER_API ElementSetInt(const char *pElementName,Int iValue);
		float BURGER_API ElementGetFloat(const char *pElementName,float fDefault) const;
		float BURGER_API ElementGetFloat(const char *pElementName,float fDefault,float fMin,float fMax) const;
		void BURGER_API ElementSetFloat(const char *pElementName,float fValue);
		double BURGER_API ElementGetDouble(const char *pElementName,double dDefault) const;
		double BURGER_API ElementGetDouble(const char *pElementName,double dDefault,double dMin,double dMax) const;
		void BURGER_API ElementSetDouble(const char *pElementName,double dValue);
		const char *BURGER_API ElementGetString(const char *pElementName,const char *pDefault) const;
		void BURGER_API ElementSetString(const char *pElementName,const char *pValue);
		static Element * BURGER_API New(InputMemoryStream *pInput);
		static Element * BURGER_API New(const char *pName);
	};
private:
	Root m_Root;				///< Root entry for a list of XML objects
	Word m_bUTF8ByteMark;		///< TRUE if the UTF-8 byte mark should be emitted on write
public:
	FileXML();
	~FileXML();
	static FileXML * BURGER_API New(void);
	static FileXML * BURGER_API New(const char *pFilename,Word bAlwaysCreate=FALSE);
	static FileXML * BURGER_API New(Filename *pFilename,Word bAlwaysCreate=FALSE);
	static FileXML * BURGER_API New(InputMemoryStream *pInput,Word bAlwaysCreate=FALSE);
	Word BURGER_API Init(const char *pFilename);
	Word BURGER_API Init(Filename *pFilename);
	Word BURGER_API Init(InputMemoryStream *pInput);
	void BURGER_API Shutdown(void);
	Word BURGER_API Save(OutputMemoryStream *pOutput) const;
	BURGER_INLINE Word GetUTF8ByteMark(void) const { return m_bUTF8ByteMark; }
	BURGER_INLINE void SetUTF8ByteMark(Word bUTF8ByteMark) { m_bUTF8ByteMark = bUTF8ByteMark; }
	static Word BURGER_API ReadXMLName(String *pOutput,InputMemoryStream *pInput);
	static Word BURGER_API ReadXMLText(String *pOutput,InputMemoryStream *pInput);
	static Word BURGER_API SaveXMLString(OutputMemoryStream *pOutput,const char *pInput);
	static Word BURGER_API DecodeXMLString(String *pInput);
	Declaration *BURGER_API FindDeclaration(Word bAlwaysCreate=FALSE);
	Declaration *BURGER_API AddDeclaration(float fVersion=1.0f,const char *pEncoding=NULL,Word bStandalone=2);
	BURGER_INLINE void DeleteDeclaration(void) { m_Root.DeleteType(Generic::XML_DECLARATION); }
	BURGER_INLINE Root * GetRoot(void) { return &m_Root; }
	BURGER_INLINE const Root * GetRoot(void) const { return &m_Root; }
	BURGER_INLINE const Element *FindElement(const char *pElementName) const { return m_Root.FindElement(pElementName); }
	BURGER_INLINE Element *FindElement(const char *pElementName,Word bAlwaysCreate=FALSE) { return m_Root.FindElement(pElementName,bAlwaysCreate); }
	BURGER_INLINE Element *AddElement(const char *pElementName) { return m_Root.AddElement(pElementName); }
	BURGER_INLINE void DeleteElement(const char *pElementName) { m_Root.DeleteElement(pElementName); }
	BURGER_INLINE void DeleteElements(const char *pElementName) { m_Root.DeleteElements(pElementName); }
	BURGER_INLINE Element * GetFirstElement(void) const { return m_Root.GetNextElement(); }
	BURGER_INLINE Generic * GetFirstItem(void) const { return m_Root.GetNextItem(); }
};
}
namespace Burger {
struct Shape8Bit_t {
	Word16 m_usWidth;	///< Width of the shape
	Word16 m_usHeight;	///< Height of the shape
	Word8 m_Data[1];	///< Raw shape data
	BURGER_INLINE Word GetWidth(void) const { return m_usWidth; }
	BURGER_INLINE Word GetHeight(void) const { return m_usHeight; }
	BURGER_INLINE const Word8 *GetPixels(void) const { return m_Data; }
	BURGER_INLINE void Draw(Renderer *pRenderer,int iX,int iY) const { pRenderer->Draw8BitPixels(iX,iY,GetWidth(),GetHeight(),GetWidth(),GetPixels()); }
	BURGER_INLINE void DrawMasked(Renderer *pRenderer,int iX,int iY) const { pRenderer->Draw8BitPixelsMasked(iX,iY,GetWidth(),GetHeight(),GetWidth(),GetPixels()); }
	static Shape8Bit_t * BURGER_API Load(RezFile *pRezFile,Word uRezNum);
	static void BURGER_API Preload(RezFile *pRezFile,Word uRezNum);
};
struct Shape8BitOffset_t {
	short m_sXOffset;			///< Signed offset for x
	short m_sYOffset;			///< Signed offset for y
	Shape8Bit_t m_Shape8Bit;	///< Shape data
	BURGER_INLINE Word GetWidth(void) const { return m_Shape8Bit.GetWidth(); }
	BURGER_INLINE Word GetHeight(void) const { return m_Shape8Bit.GetHeight(); }
	BURGER_INLINE const Word8 *GetPixels(void) const { return m_Shape8Bit.GetPixels(); }
	BURGER_INLINE int GetXOffset(void) const { return m_sXOffset; }
	BURGER_INLINE int GetYOffset(void) const { return m_sYOffset; }
	BURGER_INLINE void Draw(Renderer *pRenderer,int iX,int iY) const { pRenderer->Draw8BitPixels(iX+GetXOffset(),iY+GetYOffset(),GetWidth(),GetHeight(),GetWidth(),GetPixels()); }
	BURGER_INLINE void DrawMasked(Renderer *pRenderer,int iX,int iY) const { pRenderer->Draw8BitPixelsMasked(iX+GetXOffset(),iY+GetYOffset(),GetWidth(),GetHeight(),GetWidth(),GetPixels()); }
	static Shape8BitOffset_t * BURGER_API Load(RezFile *pRezFile,Word uRezNum);
	static void BURGER_API Preload(RezFile *pRezFile,Word uRezNum);
};
struct Shape8BitArray_t {
	Word32 m_Index[1];			///< Array of indexs to the shape array
	BURGER_INLINE Shape8Bit_t *GetShape(Word uIndex) { return reinterpret_cast<Shape8Bit_t *>(reinterpret_cast<Word8 *>(this)+m_Index[uIndex]); }
	BURGER_INLINE const Shape8Bit_t *GetShape(Word uIndex) const { return reinterpret_cast<const Shape8Bit_t *>(reinterpret_cast<const Word8 *>(this)+m_Index[uIndex]); }
	static Shape8BitArray_t * BURGER_API Load(RezFile *pRezFile,Word uRezNum);
	static void BURGER_API Preload(RezFile *pRezFile,Word uRezNum);
};
struct Shape8BitOffsetArray_t {
	Word32 m_Index[1];			///< Array of indexs to the shape array
	BURGER_INLINE Shape8BitOffset_t *GetShape(Word uIndex) { return reinterpret_cast<Shape8BitOffset_t *>(reinterpret_cast<Word8 *>(this)+m_Index[uIndex]); }
	BURGER_INLINE const Shape8BitOffset_t *GetShape(Word uIndex) const { return reinterpret_cast<const Shape8BitOffset_t *>(reinterpret_cast<const Word8 *>(this)+m_Index[uIndex]); }
	static Shape8BitOffsetArray_t * BURGER_API Load(RezFile *pRezFile,Word uRezNum);
	static void BURGER_API Preload(RezFile *pRezFile,Word uRezNum);
};
struct LWShape_t {
	Word16 Width;		/* Width of the shape */
	Word16 Height;		/* Height of the shape */
	Word8 Data[1];		/* Raw shape data */
	static LWShape_t * BURGER_API Load(RezFile *pRezFile,Word uRezNum);
	static void BURGER_API Preload(RezFile *pRezFile,Word uRezNum);
};
struct LWXShape_t {
	short XOffset;		/* Signed offset for x */
	short YOffset;		/* Signed offset for y */
	LWShape_t Shape;	/* Shape data */
	static LWXShape_t * BURGER_API Load(RezFile *pRezFile,Word uRezNum);
	static void BURGER_API Preload(RezFile *pRezFile,Word uRezNum);
};
struct GfxShape_t {
	Word8 Palette[768];	/* Palette for the shape */
	LWXShape_t XShape;	/* XShape for the actual data */
	static GfxShape_t * BURGER_API Load(RezFile *pRezFile,Word uRezNum);
	static void BURGER_API Preload(RezFile *pRezFile,Word uRezNum);
};
}
namespace Burger {
class Font {
	BURGER_DISABLECOPYCONSTRUCTORS(Font);
public:
	Font(Renderer *pRenderer=NULL);
	virtual ~Font();
	virtual void Draw(const char *pInput,WordPtr uLength);
	virtual Word GetPixelWidth(const char *pInput,WordPtr uLength);
	virtual void DrawChar(Word uLetter);
	BURGER_INLINE void SetRenderer(Renderer *pRenderer) { m_pRenderer = pRenderer; }
	BURGER_INLINE Renderer *GetRenderer(void) const { return m_pRenderer; }
	BURGER_INLINE void SetX(int iX) { m_iX = iX; }
	BURGER_INLINE void SetY(int iY) { m_iY = iY; }
	BURGER_INLINE void SetXY(int iX,int iY) { m_iX = iX; m_iY = iY; }
	BURGER_INLINE int GetX(void) const { return m_iX; }
	BURGER_INLINE int GetY(void) const { return m_iY; }
	BURGER_INLINE Word GetHeight(void) const { return m_uHeight; }
	BURGER_INLINE Word GetFirstChar(void) const { return m_uFirst; }
	BURGER_INLINE Word GetCount(void) const { return m_uCount; }
	Word GetPixelWidthChar(Word uLetter);
	Word GetPixelWidthNumber(Int32 iInput);
	Word GetPixelWidthNumber(Word32 uInput);
	Word GetPixelWidthString(const char *pInput);
	void DrawNumber(Int32 iInput);
	void DrawNumber(Word32 uInput);
	void DrawString(const char *pInput);
	void DrawStringCenterX(int iX,int iY,const char *pInput);
	void DrawStringAtXY(int iX,int iY,const char *pInput);
	WordPtr CharsForPixelWidth(const char *pInput,Word uWidth);
protected:
	Renderer *m_pRenderer;	///< Rendering context to draw into
	int m_iX;				///< X coord to draw the font
	int m_iY;				///< Y coord to draw the font
	Word m_uHeight;			///< Height of the font in pixels
	Word m_uFirst;			///< First allowable UTF32 code that can be drawn
	Word m_uCount;			///< Number of characters in the font
};
}
namespace Burger {
class Font4Bit : public Font {
	BURGER_DISABLECOPYCONSTRUCTORS(Font4Bit);
public:
	struct State_t {
		Word32 m_ColorTable[16];	///< Colors to render with
		RezFile *m_pRezFile;		///< Resource file manager
		int m_iX;					///< X coord
		int m_iY;					///< Y coord
		Word m_uRezNum;				///< Resource ID of the last font loaded
		Word m_uInvisibleColor;		///< Color to ignore for drawing
	};
	struct RGBColorList_t {
		Word8 m_uCount;			///< Number of entries
		RGBWord8_t m_Colors[1];	///< Actual data to set
	};
	Font4Bit(Renderer *pRenderer=NULL);
	virtual ~Font4Bit();
	virtual Word GetPixelWidth(const char *pInput,WordPtr uLength);
	virtual void DrawChar(Word uLetter);
	void Init(RezFile *pRezFile,Word uRezNum,const Word8 *pPalette,Renderer *pRenderer=NULL);
	void Shutdown(void);
	void SaveState(State_t *pOutput);
	void RestoreState(const State_t *pInput);
	void SetColor(Word uColorIndex,Word uColor);
	BURGER_INLINE void UseZero(void) { m_uInvisibleColor = 0x7FFF; }
	BURGER_INLINE void UseMask(void) { m_uInvisibleColor = 0; }
	void InstallToPalette(RezFile *pRezFile,Word uRezNum,const Word8 *pPalette);
	void SetColorRGBListToPalette(const RGBColorList_t *pRGBList,const Word8 *pPalette);
	void SetToPalette(const Word8 *pPalette);
protected:
	union {
		Word8 Bytes[16];	///< Color of font for 8 bit rendering
		Word16 Shorts[16];	///< Color of font for 16 bit rendering
		Word32 Words[16];	///< Color of font for 32 bit rendering
	} m_ColorTable;			///< Storage for the color tables for rendering
	RezFile *m_pRezFile;	///< Resource file manager
	void **m_ppData;		///< Handle to the active font
	WordPtr m_uPixelOffset;	///< Offset to the pixel array
	Word m_uRezNum;			///< Resource ID of the last font loaded
	Word m_uInvisibleColor;	///< Color to ignore for drawing
};
}
namespace Burger {
class CommandParameter : public Base {
	BURGER_RTTI_IN_CLASS();
	const char *m_pHelp;				///< Pointer to the optional help string
	const char *const *m_ppParameterNames;		///< Array of "C" strings of the -parameter (Minus the -)
	WordPtr m_uParameterCount;			///< Number of possible strings to check
protected:
	CommandParameter(const char *pHelp,const char * const *ppParameterNames,WordPtr uParameterCount) :
		m_pHelp(pHelp),
		m_ppParameterNames(ppParameterNames),
		m_uParameterCount(uParameterCount) {}
public:
	BURGER_INLINE Word IsHelpAvailable(void) const { return m_pHelp!=NULL; }
	BURGER_INLINE const char *GetHelp(void) const { return m_pHelp; }
	virtual int Action(int argc,const char **argv) = 0;
	static int BURGER_API RemoveParms(int argc,const char **argv,int iIndexToArgv,int iRemoveCount);
	static int Process(int argc,const char **argv,const CommandParameter **ppParms,WordPtr uParmCount,const char *pUsage=NULL,int iMin=0,int iMax=0);
};
}
namespace Burger {
class CommandParameterBooleanTrue : public CommandParameter {
	Word m_bValue;			///< \ref TRUE if triggered, \ref FALSE if not
public:
	CommandParameterBooleanTrue(const char *pHelp,const char *const *ppParameterName,WordPtr uParameterCount) :
		CommandParameter(pHelp,ppParameterName,uParameterCount),
		m_bValue(FALSE) {}
	CommandParameterBooleanTrue(const char *pHelp,const char *pParameterName) :
		CommandParameter(pHelp,reinterpret_cast<const char *const *>(pParameterName),0),
		m_bValue(FALSE) {}
	virtual int Action(int argc,const char **argv);
	BURGER_INLINE Word GetValue(void) const { return m_bValue; }
};
}
namespace Burger {
class CommandParameterWordPtr : public CommandParameter {
	WordPtr m_uValue;	///< Parsed value
	WordPtr m_uMin;		///< Lowest acceptable value
	WordPtr m_uMax;		///< Highest acceptable value
public:
	CommandParameterWordPtr(const char *pHelp,const char **ppParameterName,WordPtr uParameterCount,WordPtr uDefault,WordPtr uMin=0,WordPtr uMax=BURGER_MAXWORDPTR) :
		CommandParameter(pHelp,ppParameterName,uParameterCount),
		m_uValue(uDefault),
		m_uMin(uMin),
		m_uMax(uMax) {}
	CommandParameterWordPtr(const char *pHelp,const char *pParameterName,WordPtr uDefault,WordPtr uMin=0,WordPtr uMax=BURGER_MAXWORDPTR) :
		CommandParameter(pHelp,reinterpret_cast<const char * const *>(pParameterName),0),
		m_uValue(uDefault),
		m_uMin(uMin),
		m_uMax(uMax) {}
	virtual int Action(int argc,const char **argv);
	BURGER_INLINE WordPtr GetValue(void) const { return m_uValue; }
};
}
namespace Burger {
class CommandParameterString : public CommandParameter {
	String m_Value;		///< Parsed string
public:
	CommandParameterString(const char *pHelp,const char *const *ppParameterName,WordPtr uParameterCount,const char *pDefault=NULL) :
		CommandParameter(pHelp,ppParameterName,uParameterCount),
		m_Value(pDefault) {}
	CommandParameterString(const char *pHelp,const char *pParameterName,const char *pDefault=NULL) :
		CommandParameter(pHelp,reinterpret_cast<const char *const *>(pParameterName),0),
		m_Value(pDefault) {}
	virtual int Action(int argc,const char **argv);
	BURGER_INLINE const char *GetValue(void) const { return m_Value.GetPtr(); }
};
}
namespace Burger {
class Mouse {
public:
	enum {
		MOUSEBUFFSIZE=128			///< Number of mouse events in the event cache
	};
	enum eMouseButtons {
		BUTTON_LEFT=0x1,			///< Mask for the left mouse button
		BUTTON_RIGHT=0x2,			///< Mask for the right mouse button
		BUTTON_MIDDLE=0x4,			///< Mask for the center mouse button
		BUTTON_4=0x8,				///< Mask for the 4th mouse button
		BUTTON_5=0x10,				///< Mask for the 5th mouse button
		BUTTON_6=0x20,				///< Mask for the 6th mouse button
		BUTTON_7=0x40,				///< Mask for the 7th mouse button
		BUTTON_8=0x80,				///< Mask for the 8th mouse button
		BUTTON_9=0x100,				///< Mask for the 9th mouse button
		BUTTON_10=0x200,			///< Mask for the 10th mouse button
		BUTTON_11=0x400,			///< Mask for the 11th mouse button
		BUTTON_12=0x800,			///< Mask for the 12th mouse button
		BUTTON_13=0x1000,			///< Mask for the 13th mouse button
		BUTTON_14=0x2000,			///< Mask for the 14th mouse button
		BUTTON_15=0x4000,			///< Mask for the 15th mouse button
		BUTTON_16=0x8000			///< Mask for the 16th mouse button
	};
	enum eMouseEvent {
		EVENT_BUTTONDOWN,			///< Mouse button down event
		EVENT_BUTTONUP,				///< Mouse button up event
		EVENT_MOVE,					///< Mouse motion event
		EVENT_POSITION,				///< Mouse motion event
		EVENT_WHEEL					///< Mouse wheel event
	};
#if defined(BURGER_MACOSX) || defined(DOXYGEN)
	enum {
		MAX_MOUSE_DEVICE_COUNT=8	///< Maximum number of mice/trackpads OSX will track
	};
	struct DeviceStruct {
		__IOHIDDevice *m_pDevice;	///< Pointer to the device driver
		String m_Name;				///< Name of the device driver
		Word m_bUnplugged;			///< \ref TRUE if this device was unplugged
	};
#endif
	struct MouseDataHeader_t {
		eMouseEvent m_eEvent;		///< Mouse motion event
		Word32 m_uMSTimeStamp;		///< Time when the event occurred
	};
	struct MouseButtonData_t : public MouseDataHeader_t {
		Word32 m_uX;		///< Absolute X position on the screen
		Word32 m_uY;		///< Absolute Y position on the screen
		Word32 m_uButtons;	///< Mouse buttons
	};
	struct MouseWheelData_t : public MouseDataHeader_t {
		Int32 m_iMouseWheelX;	///< Horizontal mouse wheel motion (Apple ball mice support this)
		Int32 m_iMouseWheelY;	///< Vertical mouse wheel motion (Most mice support this)
	};
	struct MouseMotionData_t : public MouseDataHeader_t {
		Int32 m_iDeltaX;		///< Relative X motion
		Int32 m_iDeltaY;		///< Relative Y motion
	};
	struct MousePositionData_t : public MouseDataHeader_t {
		Word32 m_uX;		///< Absolute X position on the screen
		Word32 m_uY;		///< Absolute Y position on the screen
	};
	union MouseEvent_t {
		MouseDataHeader_t m_Header;		///< Header shared by all data chunks
		MouseButtonData_t m_Button;		///< Data for a EVENT_BUTTONUP or EVENT_BUTTONDOWN event
		MouseWheelData_t m_Wheel;		///< Data for a EVENT_WHEEL event
		MouseMotionData_t m_Motion;		///< Data for a EVENT_MOVE event
		MousePositionData_t m_Position;	///< Data for a EVENT_POSITION event
	};
private:
	BURGER_DISABLECOPYCONSTRUCTORS(Mouse);
	GameApp *m_pAppInstance;		///< Application instance
	CriticalSection m_MouseLock;	///< Lock for multi-threading
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
	static WordPtr BURGER_API WindowsMouseThread(void *pData);
	IDirectInputDevice8W *m_pMouseDevice;	///< Direct input device (Windows only)
	void *m_pMouseEvent;			///< Event signal for DirectInput (Windows only)
	Thread m_MouseThread;			///< Asynchronous thread monitoring DirectInput (Windows only)
	Word m_bAcquired;				///< \ref TRUE if DirectInput8 is active (Windows only)
	volatile Word32 m_bQuit;		///< \ref TRUE when the thread is shutting down (Windows only)
#endif
#if defined(BURGER_MACOSX) || defined(DOXYGEN)
	__IOHIDManager *m_pHIDManager;	///< HID Manager pointer
	DeviceStruct m_Mice[MAX_MOUSE_DEVICE_COUNT];	///< Array of mice devices
	Word m_uMiceCount;				///< Number of mice devices found
#endif
	Word32 m_uX;					///< Current X coordinate of the mouse
	Word32 m_uY;					///< Current Y coordinate of the mouse
	Word32 m_uBoundsX;				///< Screen width bounds for the mouse
	Word32 m_uBoundsY;				///< Screen height bounds for the mouse
	Int32 m_iDeltaX;				///< Accumulated X motion of the mouse
	Int32 m_iDeltaY;				///< Accumulated Y motion of the mouse
	Int32 m_iMouseWheelX;			///< Accumulated X motion of the mouse wheel
	Int32 m_iMouseWheelY;			///< Accumulated Y motion of the mouse wheel
	Word32 m_uButtons;				///< Current state of the mouse buttons
	Word32 m_uPressedButtons;		///< Mouse buttons pressed since last read
	Word m_bButtonSwap;				///< Switch the left and right buttons for lefties
	Word m_uArrayStart;				///< Read index for m_KeyEvents
	Word m_uArrayEnd;				///< Write index for m_KeyEvents
	MouseEvent_t m_MouseEvents[MOUSEBUFFSIZE];	///< Circular buffer holding mouse events
public:
	Mouse(GameApp *pAppInstance);
	~Mouse();
	Word BURGER_API PeekMouseEvent(MouseEvent_t *pEvent);
	Word BURGER_API GetMouseEvent(MouseEvent_t *pEvent);
	Word BURGER_API IsPresent(void) const;
	Word32 BURGER_API ReadButtons(void);
	Word32 BURGER_API ReadButtonDowns(void);
	void BURGER_API Read(Word32 *pX,Word32 *pY);
	void BURGER_API Read(Int32 *pX,Int32 *pY);
	Int32 BURGER_API ReadWheelX(void);
	Int32 BURGER_API ReadWheelY(void);
	void BURGER_API SetRange(Word32 x,Word32 y);
	void BURGER_API PostMousePosition(Word32 x,Word32 y,Word32 uMSTimeStamp=0);
	void BURGER_API PostMouseMotion(Int32 x,Int32 y,Word32 uMSTimeStamp=0);
	void BURGER_API PostMouseDown(Word32 uMouseBits,Word32 uMSTimeStamp=0);
	void BURGER_API PostMouseUp(Word32 uMouseBits,Word32 uMSTimeStamp=0);
	void BURGER_API PostMouseWheel(Int32 iWheelXMovement,Int32 iWheelYMovement,Word32 uMSTimeStamp=0);
	Word BURGER_API PostMouseEvent(const MouseDataHeader_t *pEvent);
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
	void BURGER_API AcquireDirectInput(void);
	void BURGER_API UnacquireDirectInput(void);
	void BURGER_API ReadSystemMouseValues(void);
#endif
#if defined(BURGER_MACOSX) || defined(DOXYGEN)
	static void EnumerationCallback(void *pData,int iReturn,void *pSender,__IOHIDDevice *pDevice);
	static void DisconnectionCallback(void *pData,int iReturn,void *pSender);
	static void InputCallback(void *pData,int iReturn,void *pSender,__IOHIDValue *pValue);
	static RunQueue::eReturnCode BURGER_API Poll(void *pData);
#endif
};
}
namespace Burger {
class Keyboard {
public:
	enum {
		KEYCAPDOWN=0x01,	///< If \ref TRUE in m_KeyArray, this key is currently held down
		KEYCAPPRESSED=0x02,	///< If \ref TRUE in m_KeyArray, this key was pressed, but wasn't acknowledged by the application
		KEYCAPTOGGLE=0x4,	///< If \ref TRUE in m_KeyArray, this key is toggled "on"
		KEYBUFFSIZE=128		///< Number of keystrokes in keyboard cache
	};
	enum eAsciiCode {
		ASCII_BACKSPACE=0x08,	///< Backspace key
		ASCII_TAB=0x09,			///< Tab key
		ASCII_ENTER=0x0D,		///< Return/enter key
		ASCII_RETURN=0x0D,		///< Return/enter key
		ASCII_ESCAPE=0x1B,		///< Escape key
		ASCII_ESC=0x1B,			///< Escape key
		ASCII_SPACE=0x20,		///< Space bar
		ASCII_F1=0x80,			///< F1 key
		ASCII_F2=0x81,			///< F2 key
		ASCII_F3=0x82,			///< F3 key
		ASCII_F4=0x83,			///< F4 key
		ASCII_F5=0x84,			///< F5 key
		ASCII_F6=0x85,			///< F6 key
		ASCII_F7=0x86,			///< F7 key
		ASCII_F8=0x87,			///< F8 key
		ASCII_F9=0x88,			///< F9 key
		ASCII_F10=0x89,			///< F10 key
		ASCII_F11=0x8A,			///< F11 key
		ASCII_F12=0x8B,			///< F12 key
		ASCII_F13=0x8C,			///< F12 key
		ASCII_F14=0x8D,			///< F12 key
		ASCII_F15=0x8E,			///< F12 key
		ASCII_PAUSE=0x8F,		///< Pause key
		ASCII_SCROLLLOCK=0x090,	///< Scroll lock key
		ASCII_HOME=0x91,		///< Home key
		ASCII_END=0x92,			///< End key
		ASCII_LEFTARROW=0x2190,	///< Left arrow key
		ASCII_UPARROW=0x2191,	///< Up arrow key
		ASCII_RIGHTARROW=0x2192,///< Right arrow key
		ASCII_DOWNARROW=0x2193,	///< Down arrow key
		ASCII_PAGEUP=0x21DE,	///< Page up key
		ASCII_PAGEDOWN=0x21DF,	///< Page down key
		ASCII_DELETE=0x232B,	///< Delete key
		ASCII_INSERT=0x2380,	///< Insert key
		ASCII_PRINTSCREEN=0x2399 ///< Printscreen key
	};
	enum eScanCode {
		SC_INVALID,			///< Zero means no key
		SC_A,				///< A Key
		SC_B,				///< B Key
		SC_C,				///< C Key
		SC_D,				///< D Key
		SC_E,				///< E Key
		SC_F,				///< F Key
		SC_G,				///< G Key
		SC_H,				///< H Key
		SC_I,				///< I Key
		SC_J,				///< J Key
		SC_K,				///< K Key
		SC_L,				///< L Key
		SC_M,				///< M Key
		SC_N,				///< N Key
		SC_O,				///< O Key
		SC_P,				///< P Key
		SC_Q,				///< Q Key
		SC_R,				///< R Key
		SC_S,				///< S Key
		SC_T,				///< T Key
		SC_U,				///< U Key
		SC_V,				///< V Key
		SC_W,				///< W Key
		SC_X,				///< X Key
		SC_Y,				///< Y Key
		SC_Z,				///< Z Key
		SC_FUSS,			///< German ss
		SC_0,				///< )/0 Key
		SC_1,				///< !/1 Key
		SC_2,				///< @/2 Key
		SC_3,				///< #/3 Key
		SC_4,				///< $/4 Key
		SC_5,				///< %/5 Key
		SC_6,				///< ^/6 Key
		SC_7,				///< &/7 Key
		SC_8,				///< */8 Key
		SC_9,				///< (/9 Key
		SC_TILDE,			///< ~/` Key
		SC_UNDERSCORE,		///< _/- Key
		SC_MINUS=SC_UNDERSCORE,	///< _/- Key
		SC_PLUS,			///< +/= Key
		SC_EQUALS=SC_PLUS,	///< +/= Key
		SC_BACKSPACE,		///< Backspace key
		SC_RIGHTBRACE,		///< {/[ key
		SC_RIGHTBRACKET=SC_RIGHTBRACE,	///< {/[ key
		SC_LEFTBRACE,		///< }/] key
		SC_LEFTBRACKET=SC_LEFTBRACE,	///< }/] key
		SC_RETURN,			///< Return key
		SC_QUOTE,			///< "/' key
		SC_GRAVE=SC_QUOTE,	///< "/' key
		SC_COLON,			///< :/; key
		SC_SEMICOLON=SC_COLON,	///< :/; key
		SC_VERTBAR,			///< |/\ key
		SC_BACKSLASH=SC_VERTBAR,	///< |/\ key
		SC_COMMA,			///< </, key
		SC_PERIOD,			///< >/. key
		SC_SLASH,			///< ?// key
		SC_TAB,				///< Tab key
		SC_SPACE,			///< Spacebar
		SC_POWERBOOKENTER,	///< Mac powerbook enter key
		SC_ESCAPE,			///< Escape key
		SC_LEFTCONTROL,		///< Left control key
		SC_RIGHTCONTROL,	///< Right control key
		SC_LEFTOPTION,		///< Left option key
		SC_RIGHTOPTION,		///< Right option key
		SC_LEFTALT,			///< Left Alt/Apple key
		SC_LEFTOPENAPPLE=SC_LEFTALT,	///< Left Alt/Apple key
		SC_RIGHTALT,		///< Right Alt/Apple key
		SC_RIGHTOPENAPPLE=SC_RIGHTALT,	///< Right Alt/Apple key
		SC_LEFTSHIFT,		///< Left shift key
		SC_RIGHTSHIFT,		///< Right shift key
		SC_LEFTMENU,		///< Left menu key
		SC_RIGHTMENU,		///< Right menu key
		SC_CAPSLOCK,		///< Caps lock key
		SC_KEYPADPERIOD,	///< Keypad period
		SC_KEYPADCOMMA,		///< Keypad comma (NEC PC98)
		SC_KEYPADASTERISK,	///< Keypad asterisk
		SC_KEYPADPLUS,		///< Keypad +
		SC_NUMLOCK,			///< Numlock
		SC_KEYPADSLASH,		///< Keypad divide
		SC_KEYPADENTER,		///< Keypad enter
		SC_KEYPADMINUS,		///< Keypad -
		SC_KEYPADEQUALS,	///< Keypad =
		SC_KEYPAD0,			///< Keypad 0
		SC_KEYPAD1,			///< Keypad 1
		SC_KEYPAD2,			///< Keypad 2
		SC_KEYPAD3,			///< Keypad 3
		SC_KEYPAD4,			///< Keypad 4
		SC_KEYPAD5,			///< Keypad 5
		SC_KEYPAD6,			///< Keypad 6
		SC_KEYPAD7,			///< Keypad 7
		SC_KEYPAD8,			///< Keypad 8
		SC_KEYPAD9,			///< Keypad 9
		SC_PRINTSCREEN,		///< Print screen
		SC_SYSRQ=SC_PRINTSCREEN,	///< System	Request
		SC_SCROLLLOCK,		///< Scroll lock
		SC_PAUSE,			///< Pause key
		SC_INSERT,			///< Insert key
		SC_DELETE,			///< Delete key
		SC_HOME,			///< Home key
		SC_END,				///< End key
		SC_PAGEUP,			///< Pageup key
		SC_PAGEDOWN,		///< Pagedown key
		SC_LEFTARROW,		///< Left arrow key
		SC_RIGHTARROW,		///< Right arrow key
		SC_DOWNARROW,		///< Down arrow key
		SC_UPARROW,			///< Up arrow key
		SC_F1,				///< Function key 1
		SC_F2,				///< Function key 2
		SC_F3,				///< Function key 3
		SC_F4,				///< Function key 4
		SC_F5,				///< Function key 5
		SC_F6,				///< Function key 6
		SC_F7,				///< Function key 7
		SC_F8,				///< Function key 8
		SC_F9,				///< Function key 9
		SC_F10,				///< Function key 10
		SC_F11,				///< Function key 11
		SC_F12,				///< Function key 12
		SC_F13,				///< Function key 13
		SC_F14,				///< Function key 14
		SC_F15,				///< Function key 15
		SC_OEM_102,			///< <> or \| on RT 102-key keyboard (Non-U.S.)
		SC_KANA,			///< (Japanese keyboard)
		SC_ABNT_C1,			///< /? on Brazilian keyboard
		SC_CONVERT,			///< (Japanese keyboard)
		SC_NOCONVERT,		///< (Japanese keyboard)
		SC_YEN,				///< (Japanese keyboard)
		SC_ABNT_C2,			///< Numpad . on Brazilian keyboard
		SC_PREVTRACK,		///< Previous Track (CIRCUMFLEX on Japanese keyboard)
		SC_AT,				///< (NEC PC98)
		SC_COLONPC98,		///< (NEC PC98)
		SC_UNDERLINE,		///< (NEC PC98)
		SC_KANJI,			///< (Japanese keyboard)
		SC_STOP,			///< (NEC PC98)
		SC_AX,				///< (Japan AX)
		SC_UNLABELED,		///< (J3100)
		SC_NEXTTRACK,		///< Next Track
		SC_MUTE,			///< Mute
		SC_CALCULATOR,		///< Calculator
		SC_PLAYPAUSE,		///< Play / Pause
		SC_MEDIASTOP,		///< Media Stop
		SC_VOLUMEDOWN,		///< Volume -
		SC_VOLUMEUP,		///< Volume +
		SC_WEBHOME,			///< Web home
		SC_APPS,			///< AppMenu key
		SC_POWER,			///< System Power
		SC_SLEEP,			///< System Sleep
		SC_WAKE,			///< System Wake
		SC_WEBSEARCH,		///< Web Search
		SC_WEBFAVORITES,	///< Web Favorites
		SC_WEBREFRESH,		///< Web Refresh
		SC_WEBSTOP,			///< Web Stop
		SC_WEBFORWARD,		///< Web Forward
		SC_WEBBACK,			///< Web Back
		SC_MYCOMPUTER,		///< My Computer
		SC_MAIL,			///< Mail
		SC_MEDIASELECT,		///< Media Select
		SC_EXTRA,			///< Extra key codes
		SC_MAXENTRY=255		///< Highest scan code valid value
	};
	enum eKeyFlags {
		FLAG_KEYDOWN=0x01,	///< Key is pressed
		FLAG_ALT=0x02,		///< Alt/Open Apple key is held down at the same time
		FLAG_CONTROL=0x04,	///< Control key is held down at the same time
		FLAG_OPTION=0x08,	///< Option key is held down at the same time
		FLAG_SHIFT=0x10,	///< Shift key is held down at the same time
		FLAG_REPEAT=0x20,	///< This is a auto generated repeat key
		FLAG_CAPSLOCK=0x40,	///< Caps lock is active,
		FLAG_NUMLOCK=0x80	///< Num lock is active
	};
	struct KeyEvent_t {
		Word32 m_uAscii;	///< Unicode ASCII value
		Word16 m_uFlags;	///< Flags for key modifiers
		Word16 m_uScanCode;	///< Scan code of the key
		Word32 m_uMSTimeStamp;	///< Timestamp of when this event was recorded
	};
private:
	BURGER_DISABLECOPYCONSTRUCTORS(Keyboard);
	GameApp *m_pAppInstance;			///< Application instances
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
	static WordPtr BURGER_API WindowsKeyboardThread(void *pData);
	IDirectInputDevice8W* m_pKeyboardDevice;	///< DirectInput Device reference (WINDOWS only)
	void *m_pKeyboardEvent;			///< Event signal for DirectInput (Windows only)
	void *m_pKeyboardTimerEvent;	///< Keyboard repeat timer event (Windows only)
	Thread m_KeyboardThread;		///< Asynchronous thread monitoring DirectInput (Windows only)
	CriticalSection m_KeyboardLock;	///< Lock for multi-threading (Windows only)
	Word m_bAcquired;				///< \ref TRUE if DirectInput8 is active (Windows only)
	Word m_bRepeatActive;			///< \ref TRUE if auto repeat time is active (Windows only)
	volatile Word32 m_bQuit;		///< \ref TRUE when the thread is shutting down (Windows only)
#endif
#if defined(BURGER_XBOX360)
	static RunQueue::eReturnCode BURGER_API Poll(void *pData);
#endif
#if defined(BURGER_MACOSX) || defined(DOXYGEN)
	CriticalSection m_KeyboardLock;	///< Lock for multi-threading (MacOSX only)
#endif
	Word8 m_KeyArray[SC_MAXENTRY+1];	///< Array with the current state of the keyboard
	Word m_uArrayStart;					///< Read index for m_KeyEvents
	Word m_uArrayEnd;					///< Write index for m_KeyEvents
	Word m_uInitialDelay;				///< Initial delay in ms for autorepeat
	Word m_uRepeatDelay;				///< Delay between repeating keystrokes
	KeyEvent_t m_KeyEvents[KEYBUFFSIZE];	///< Circular buffer holding keyboard events
	KeyEvent_t m_RepeatEvent;			///< Event to post on a repeat
public:
	Keyboard(GameApp *pAppInstance);
	~Keyboard();
	Word BURGER_API PeekKeyEvent(KeyEvent_t *pEvent);
	Word BURGER_API GetKeyEvent(KeyEvent_t *pEvent);
	void BURGER_API ClearKey(eScanCode uScanCode);
	eScanCode BURGER_API AnyPressed(void);
	Word BURGER_API HasBeenPressed(eScanCode uScanCode);
	Word BURGER_API HasBeenPressedClear(eScanCode uScanCode);
	Word BURGER_API IsPressed(eScanCode uScanCode);
	Word BURGER_API GetKey(void);
	Word BURGER_API GetKeyLowerCase(void);
	Word BURGER_API GetKeyUpperCase(void);
	void BURGER_API Flush(void);
	Word BURGER_API Wait(void);
	Word BURGER_API PostKeyDown(eScanCode uScanCode);
	Word BURGER_API PostKeyUp(eScanCode uScanCode);
	Word BURGER_API PostKeyEvent(const KeyEvent_t *pEvent);
	Word BURGER_API EncodeScanCode(KeyEvent_t *pEvent,eScanCode uScanCode);
	static eScanCode BURGER_API StringToScanCode(const char *pString);
	static void BURGER_API ScanCodeToString(char *pString,WordPtr uStringSize,eScanCode uScanCode);
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
	Word BURGER_API PostWindowsKeyDown(Word32 uScanCode);
	Word BURGER_API PostWindowsKeyUp(Word32 uScanCode);
	Word BURGER_API EncodeWindowsScanCode(KeyEvent_t *pEvent,Word uWindowsCode);
	void BURGER_API AcquireDirectInput(void);
	void BURGER_API UnacquireDirectInput(void);
	void BURGER_API ReadSystemKeyboardDelays(void);
#endif
#if defined(BURGER_MACOSX) || defined(DOXYGEN)
	void BURGER_API ProcessEvent(NSEvent *pEvent);
#endif
};
}
namespace Burger {
class Joypad {
public:
	enum {
		AXIS1MIN=0x1,			///< Joystick Axis 1 minimum motion button
		AXIS1MAX=0x2,			///< Joystick Axis 1 maximum motion button
		AXIS2MIN=0x4,			///< Joystick Axis 2 minimum motion button
		AXIS2MAX=0x8,			///< Joystick Axis 2 maximum motion button
		AXIS3MIN=0x10,			///< Joystick Axis 3 minimum motion button
		AXIS3MAX=0x20,			///< Joystick Axis 3 maximum motion button
		AXIS4MIN=0x40,			///< Joystick Axis 4 minimum motion button
		AXIS4MAX=0x80,			///< Joystick Axis 4 maximum motion button
		POVLEFT=0x100,			///< POV left button
		POVRIGHT=0x200,			///< POV right button
		POVUP=0x400,			///< POV up button
		POVDOWN=0x800,			///< POV down button
		BUTTON1=0x1000,			///< 1st joystick button
		BUTTON2=0x2000,			///< 2nd joystick button
		BUTTON3=0x4000,			///< 3rd joystick button
		BUTTON4=0x8000,			///< 4th joystick button
		BUTTON5=0x10000,		///< 5th joystick button
		BUTTON6=0x20000,		///< 6th joystick button
		BUTTON7=0x40000,		///< 7th joystick button
		BUTTON8=0x80000,		///< 8th joystick button
		BUTTON9=0x100000,		///< 9th joystick button
		BUTTON10=0x200000,		///< 10th joystick button
		BUTTON11=0x400000,		///< 11th joystick button
		BUTTON12=0x800000,		///< 12th joystick button
		BUTTON13=0x1000000,		///< 13th joystick button
		BUTTON14=0x2000000,		///< 14th joystick button
		BUTTON15=0x4000000,		///< 15th joystick button
		BUTTON16=0x8000000,		///< 16th joystick button
		BUTTON17=0x10000000,	///< 17th joystick button
		BUTTON18=0x20000000,	///< 18th joystick button
		BUTTON19=0x40000000,	///< 19th joystick button
		BUTTON20=0x80000000		///< 20th joystick button
	};
	enum {
		MAXAXIS=6,			///< Maximum number of joystick axises
#if defined(BURGER_XBOX360) || defined(BURGER_PS3)
		MAXJOYSTICKS=4,		///< 4 joystick ports on the Xbox 360 and PS3
#else
		MAXJOYSTICKS=8,		///< Maximum number of simultaneous joysticks
#endif
		MAXBUTTONS=20,		///< Maximum number of button controls
		MAXPOV=1,			///< Maximum number of POV controllers
		MAXAXISVALUE=255,	///< Maximum Axis value
		POVANALOGFORWARD=0,		///< POV Forward value
		POVANALOGRIGHT=9000,	///< POV Right value
		POVANALOGBACKWARD=18000,	///< POV Backward value
		POVANALOGLEFT=27000,		///< POV Left value
		MAXPOVVALUE=36000,	///< Maximum POV value
		INVALIDPOVVALUE=0xFFFFFFFF,	///< Invalid POV value
		POV_SLOP=1500		///< Slop value for POV to digital conversion (15 degrees)
	};
	struct JoypadRange_t {
		Word m_uMin;					///< Minimum value for a digital \ref TRUE
		Word m_uMax;					///< Maximum value for a digital \ref TRUE
	};
	struct JoypadData_t {
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
		IDirectInputDevice8W* m_pJoystickDevice;	///< DirectInput Device reference (WINDOWS only)
#endif
		Word m_bActive;					///< \ref TRUE if it's active and/or plugged in
		Word m_uButtonCount;			///< Number of buttons on this joypad
		Word m_uPOVCount;				///< Number of POV units on this joypad
		Word m_uAxisCount;				///< Number of Axis units on this joypad
		Word32 m_uButtonState;			///< Buttons currently pressed
		Word32 m_uButtonStatePressed;	///< Buttons pressed between reads (Clicked)
		Word32 m_uAxis[MAXAXIS];		///< Axis data from the joypad (0-255)
		Word m_uAxisPercents[MAXAXIS];	///< Cache for percentages
		JoypadRange_t m_uAxisDigitalRanges[MAXAXIS];	///< Digital ranges
	};
private:
	static RunQueue::eReturnCode BURGER_API Poll(void *pData);
	Joypad(Joypad const &);						///< Prevent copying
	Joypad & operator = (Joypad const &);			///< Prevent copying
	GameApp *m_pAppInstance;							///< Application instances
#if defined(BURGER_WINDOWS)
	GUID m_GamePadGUID[MAXJOYSTICKS];					///< GUIDs for each joystick device
#endif
	JoypadData_t m_Data[MAXJOYSTICKS];					///< Current input data from game devices
	Word m_uDeviceCount;								///< Number of game controller drivers found
public:
	Joypad(GameApp *pAppInstance);
	~Joypad();
	Word32 ReadButtons(Word uWhich) const;
	Word ReadAbsolute(Word uWhich,Word uAxis) const;
	int ReadDelta(Word uWhich,Word uAxis) const;
	Word GetAxisCount(Word uWhich) const;
	void SetDigital(Word uWhich,Word uAxis,Word uPercent=20);
	BURGER_INLINE Word GetDeviceCount(void) const { return m_uDeviceCount; }
#if defined(BURGER_WINDOWS)
	void Acquire(void);
	void Unacquire(void);
#endif
};
}
#if !defined(DOXYGEN)
#ifndef _WAVEFORMATEX_
#define _WAVEFORMATEX_
typedef struct WAVEFORMATEX {
	Word16 wFormatTag;		///< format type
	Word16 nChannels;		///< number of channels (i.e. mono, stereo...)
	Word32 nSamplesPerSec;	///< sample rate
	Word32 nAvgBytesPerSec;	///< for buffer estimation
	Word16 nBlockAlign;		///< block size of data
	Word16 wBitsPerSample;	///< number of bits per sample of mono data
	Word16 cbSize;			///< the count in bytes of the size of extra information (after cbSize)
} WAVEFORMATEX,*PWAVEFORMATEX,*NPWAVEFORMATEX, *LPWAVEFORMATEX;
#endif
#endif
namespace Burger {
class Sound {
	BURGER_DISABLECOPYCONSTRUCTORS(Sound);
public:
	typedef void (BURGER_API *CompletionProc)(void *);
	enum {
		MAXVOICECOUNT = 32,			///< Maximum number of simultainous tones to mix for output
		FLAGDOUBLEBUFFER=0x4000,	///< Double buffered
		FLAGSTEREO=0x8000			///< Stereo sound
	};
	enum CodecCommand {
		CODECINIT,		///< Initialize a sound codec
		CODECSHUTDOWN,	///< Shut down a sound codec
		CODECDECODE,	///< Decode sound data
		CODECRESET		///< Reset a sound codec
	};
	enum DataType {
		TYPEBYTE,		///< Unsigned 8 bit data
		TYPECHAR,		///< Signed 8 bit data
		TYPELSHORT,		///< Little endian short
		TYPEBSHORT,		///< Big endian short
		TYPEADPCM,		///< MS ADPCM compression
		TYPEDVIPCM,		///< Intel DVI ADPCM compression
		TYPEMP3,		///< MP3 Audio
		TYPEULAW,		///< MuLaw
		TYPEALAW,		///< ALaw
		TYPEMACE3,		///< Mace 3:1
		TYPEMACE6,		///< Mace 6:1
		TYPEOGG			///< OGG/Vorbis Audio
	};
	class Voice;
	class Buffer {
		BURGER_DISABLECOPYCONSTRUCTORS(Buffer);
	public:
		Buffer();
		Buffer(const void *pBuffer,WordPtr uLength,DataType eType);
		virtual ~Buffer();
		void Shutdown(void);
		BURGER_INLINE void SetDefaultVolume(Word uVolume) { m_uDefaultVolume = uVolume; }
		BURGER_INLINE Word GetDefaultVolume(void) const { return m_uDefaultVolume; }
		BURGER_INLINE void SetDefaultPan(Word uPan) { m_uDefaultPan = uPan; }
		BURGER_INLINE Word GetDefaultPan(void) const { return m_uDefaultPan; }
		BURGER_INLINE void SetDefaultSampleRate(Word uSampleRate) { m_uDefaultSampleRate = uSampleRate; }
		BURGER_INLINE Word GetSampleRate(void) const { return m_uDefaultSampleRate; }
		BURGER_INLINE void SetCompletionFunction(CompletionProc pCompletionProc, void *pData=NULL) { m_CompletionProc = pCompletionProc; m_pCompletionData = pData; }
		BURGER_INLINE CompletionProc GetCompletionFunction(void) const { return m_CompletionProc; }
		BURGER_INLINE void *GetCompletionFunctionData(void) const { return m_pCompletionData; }
		BURGER_INLINE Word IsPlaying(void) const { return m_bPlaying; }
	protected:
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
		IDirectSoundBuffer *m_pDirectSoundBuffer8;	///< DirectSound buffer (Windows Only)
		volatile Word32 m_bTaken;	///< \ref FALSE if a voice is using the m_pDirectSoundBuffer8
		Voice *m_pOwnerVoice;		///< Voice object that is borrowing the m_pDirectSoundBuffer8
#endif
		Word8 *m_pBuffer;		///< Pointer to the data
		CompletionProc m_CompletionProc;	///< Completion routine
		void *m_pCompletionData;			///< Data to pass for completion routine
		WordPtr m_uBufferSize;	///< Length of the data in bytes
		WordPtr	m_uLoopStart;	///< Sample to start from
		WordPtr m_uLoopEnd;		///< Sample to end the loop (0 for no looping)
		DataType m_eDataType;	///< Type of data found
		Word m_uDefaultSampleRate;	///< Samples per second to play
		Word m_uDefaultPan;			///< Pan setting
		Word m_uDefaultVolume;		///< Volume for the buffer
		Word m_bPlaying;			///< \ref TRUE if the sound is currently playing
	};
	class Voice {
	public:
		Voice();
		~Voice();
		void Shutdown(void);
		Word SetVolume(Word uVolume);
		BURGER_INLINE Word GetVolume(void) const { return m_uVolume; }
		Word SetPan(Word uPan);
		BURGER_INLINE Word GetPan(void) const { return m_uPan; }
		Word SetSampleRate(Word uSamplesPerSecond);
		BURGER_INLINE Word GetSampleRate(void) const { return m_uSampleRate; }
		BURGER_INLINE Word IsPlaying(void) const { return m_bPlaying; }
	private:
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
		IDirectSoundBuffer *m_pDirectSoundBuffer8;	///< DirectSound buffer (Windows Only)
#endif
		Buffer *m_pBuffer;		///< Sound buffer to play
		WordPtr	m_uLoopStart;	///< Sample to start from
		WordPtr m_uLoopEnd;		///< Sample to end the loop (0 for no looping)
		Word m_uSampleRate;		///< Samples per second to play
		Word m_uPan;			///< Pan setting
		Word m_uVolume;			///< Volume for the buffer
		Word m_bPlaying;		///< \ref TRUE if the sound is currently playing
	};
	class Cookie {
		BURGER_DISABLECOPYCONSTRUCTORS(Cookie);
	public:
		Cookie() : m_pVoice(NULL) {}
	private:
		Voice *m_pVoice;		///< Pointer to the active voice
	};
	Sound(GameApp *pGameApp);
	~Sound();
	Word Init(void);
	void Shutdown(void);
	Word Play(Buffer *pInput,Voice *pCookie=NULL);
	Word Stop(void);
	Word Pause(void);
	Word Resume(void);
	void SetMaxVoices(Word uMax);
	BURGER_INLINE Word GetMaxVoices(void) const { return m_uMaxVoices; }
	BURGER_INLINE Word GetActiveVoiceCount(void) const { return m_uActiveVoices; }
	void SetVolume(Word uVolume);
	BURGER_INLINE Word GetVolume(void) const { return m_uVolume; }
private:
	static RunQueue::eReturnCode BURGER_API Callback(void *);
	GameApp *m_pGameApp;						///< Reference to the game application
#if defined(BURGER_WINDOWS) || defined(DOXYGEN)
	static unsigned long __stdcall ThreadCallback(void *pThis);
public:
	static const Int16 BURGER_ALIGN(g_DirectSoundVolumes[256],16);
private:
	IDirectSound8 *m_pDirectSound8Device;		///< Primary DirectSound Device (Windows Only)
	IDirectSound3DListener *m_pDirectSound3DListener;	///< Object for 3D audio origin (Windows Only)
	void *m_hCallback;						///< HANDLE of the callback thread (Windows only)
	unsigned long m_uCallbackID;					///< ID of the callback thread (Windows only)
	Word m_uDeviceFlags;					///< DSCAPS for DirectSound Device (Windows Only)
	Word m_uBufferAllocationType;			///< Preferred method of allocating audio memory (Windows Only)
	void *m_hEvents[MAXVOICECOUNT];			///< Events for DirectSound completion functions (Windows Only)
#endif
	Voice m_ActiveVoices[MAXVOICECOUNT];	///< Array of active sound buffers being played
	Word m_uActiveVoices;			///< Number of active voices
	Word m_uMaxVoices;				///< Maximum number of voices supported for mixing
	Word m_uVolume;					///< Current volume
	Word m_bStereoAvailable;		///< \ref TRUE if stereo is supported
	Word m_bBufferDepth;			///< Bits per sample the output DAC supports (8 or 16 bit)
	Word m_uOutputSamplesPerSecond;	///< Maximum sample rate the mixer supports
};
class SoundBufferRez : public Sound::Buffer {
public:
	SoundBufferRez(void);
	SoundBufferRez(RezFile *pRezFile,Word uRezNum);
	~SoundBufferRez();
	void Shutdown();
	void Set(RezFile *pRezFile,Word uRezNum);
	void Set(Word uRezNum);
private:
	RezFile *m_pRezFile;
	void **m_ppHandle;
	Word m_uRezNum;
};
}
namespace Burger {
extern void BURGER_API ChooseGridSize(Word* pXCellCount,Word* pYCellCount,const Vector4D_t *pBoundingRect,WordPtr uItemCountEstimate,float fGridScale = 0.707f);
class GridIndexPoints {
public:
	struct Entry_t {
		Vector2D_t m_Point;	///< X,Y coordinate of the grid location
		Entry_t *m_pNext;	///< Pointer to the next item at this location
		Word m_uValue;		///< Value at this location
	};
private:
	Vector4D_t m_BoundsRect;	///< Rectangle encompassing the area of the grid
	Entry_t **m_ppGrid;			///< Array of pointers for grid objects
	Word m_uXCells;				///< Number of cells wide
	Word m_uYCells;				///< Number of cells high
	float m_fXCells;			///< Number of cells wide as a float
	float m_fYCells;			///< Number of cells high as a float
	BURGER_INLINE Entry_t *GetCell(Word uX,Word uY) const
	{
		BURGER_ASSERT(uX < m_uXCells);
		BURGER_ASSERT(uY < m_uYCells);
		return m_ppGrid[(uY * m_uXCells) + uX];
	}
	BURGER_INLINE WordPtr GetCellIndex(const Vector2D_t *pInput) const
	{
		BURGER_ASSERT(pInput->x < m_fXCells);
		BURGER_ASSERT(pInput->y < m_fYCells);
		Word uX = static_cast<Word>(static_cast<int>(pInput->x));
		Word uY = static_cast<Word>(static_cast<int>(pInput->y));
		return static_cast<WordPtr>(uY * m_uXCells) + uX;
	}
	void BURGER_API GetContainingCellClamped(Vector2D_t *pOutput,const Vector2D_t *pInput) const;
public:
	GridIndexPoints(const Vector4D_t *pBounds,Word uXCells,Word uYCells);
	GridIndexPoints(const Vector4D_t *pBounds,WordPtr uItemCountEstimate,float fGridScale = 0.707f);
	~GridIndexPoints();
	BURGER_INLINE const Vector4D_t *GetBoundsRect(void) const { return &m_BoundsRect; }
	struct iterator {
		const GridIndexPoints *m_pParent;	///< Pointer to parent class
		Entry_t *m_pEntry;					///< Current object
		Vector4D_t m_QueryRect;				///< Rect of interest
		Rect_t m_QueryCellsRect;			///< Bounds rectangle in cells
		Word m_uCurrentCellX;				///< Last accessed cell X coordinate
		Word m_uCurrentCellY;				///< Last accessed cell Y coordinate
		iterator(const GridIndexPoints *pParent) :
			m_pParent(pParent),
			m_pEntry(NULL),
			m_uCurrentCellX(0),
			m_uCurrentCellY(0) {
			m_QueryRect.Zero();
			m_QueryCellsRect.Clear();
		}
		BURGER_INLINE Word at_end(void) const { return !m_pEntry; }
		BURGER_INLINE void operator++() { if (m_pEntry) { advance(); }}
		void BURGER_API advance(void);
		BURGER_INLINE Entry_t &operator*() const { BURGER_ASSERT(m_pEntry != NULL); return *m_pEntry; }
		BURGER_INLINE Entry_t *operator->() const { BURGER_ASSERT(m_pEntry != NULL); return m_pEntry; }
	};
	iterator begin(const Vector4D_t *pInput) const;
	BURGER_INLINE iterator end(void) const { return iterator(this); }
	void BURGER_API add(const Vector2D_t *pPoint,Word uValue);
	void BURGER_API remove(Entry_t *pEntry);
	iterator find(const Vector2D_t *pPoint,Word uValue);
};
class GridIndexBox {
public:
	struct Entry {
		Vector4D_t m_BoundsRect;		///< Bounds rect for testing
		Word m_uValue;					///< Payload in the object
		Word m_uQueryCount;				///< Search ID number
		Entry() : m_uQueryCount(0) {}
	};
private:
	Vector4D_t m_BoundsRect;			///< Bounds rectangle for the grid
	SimpleArray<Entry* > *m_pGrid;		///< Array of pointers to arrays in the grid
	Word m_uXCells;						///< Number of cells wide
	Word m_uYCells;						///< Number of cells high
	float m_fXCells;					///< Number of cells wide as a float
	float m_fYCells;					///< Number of cells high as a float
	Word m_uQueryCount;					///< Token for iterating over the grid
	BURGER_INLINE SimpleArray<Entry*>* GetCell(Word uX,Word uY) const {
		BURGER_ASSERT(uX < m_uXCells);
		BURGER_ASSERT(uY < m_uYCells);
		return &m_pGrid[(uY * m_uXCells) + uX];
	}
	void BURGER_API GetContainingCellClamped(Vector2D_t *pOutput,const Vector2D_t *pInput) const;
	void BURGER_API GetContainingCellsClamped(Vector4D_t *pOutput,const Vector4D_t *pInput) const;
public:
	GridIndexBox(const Vector4D_t *pBounds,Word uXCells,Word uYCells);
	GridIndexBox(const Vector4D_t *pBounds,WordPtr uItemCountEstimate,float fGridScale = 0.707f);
	~GridIndexBox();
	BURGER_INLINE const Vector4D_t *GetBounds(void) const { return &m_BoundsRect; }
	BURGER_INLINE Word GetQueryCount(void) const { return m_uQueryCount; }
	struct iterator {
		const GridIndexBox *m_pParent;		///< Pointer to parent class
		Entry *m_pEntry;					///< Current object
		Vector4D_t m_QueryRect;				///< Rect of interest
		Rect_t m_QueryCellsRect;			///< Bounds rectangle in cells
		Word m_uCurrentCellX;				///< Last accessed cell X coordinate
		Word m_uCurrentCellY;				///< Last accessed cell Y coordinate
		WordPtr m_uCurrentCellArrayIndex;	///< Index to the current entry's array
		iterator(const GridIndexBox *pParent) :
			m_pParent(pParent),
			m_pEntry(NULL),
			m_uCurrentCellX(0),
			m_uCurrentCellY(0),
			m_uCurrentCellArrayIndex(BURGER_MAXWORDPTR) {
			m_QueryRect.Zero();
			m_QueryCellsRect.Clear();
		}
		BURGER_INLINE Word at_end(void) const { return !m_pEntry; }
		BURGER_INLINE void operator++() { if (m_pEntry) { advance(); }}
		void BURGER_API advance(void);
		Word BURGER_API AdvanceInCell(void);
		BURGER_INLINE Entry &operator*() const { BURGER_ASSERT(m_pEntry != NULL); return *m_pEntry; }
		BURGER_INLINE Entry *operator->() const { BURGER_ASSERT(m_pEntry != NULL); return m_pEntry; }
	};
	iterator begin(const Vector4D_t *pBounds);
	BURGER_INLINE iterator begin_all(void) { return begin(&m_BoundsRect); }
	BURGER_INLINE iterator end(void) const { return iterator(this); }
	void BURGER_API add(const Vector4D_t *pBounds,Word uValue);
	void BURGER_API remove(Entry *pEntry);
	iterator find(const Vector4D_t *pBounds,Word uValue);
	Entry * BURGER_API FindData(const Vector2D_t *pPoint,Word uValue) const;
};
}
namespace Burger {
extern void BURGER_API EdgeIntersectTest(float *pEdge1VSEdge2,float *pEdge2VSEdge1,const Vector2D_t *pEdge1V1,const Vector2D_t *pEdge1V2,const Vector2D_t *pEdge2V1,const Vector2D_t *pEdge2V2);
}
namespace Burger { namespace Flash {
class Manager;
class Stream {
	InputMemoryStream *m_pStream;		///< Pointer to the input stream
	const Manager *m_pFlashPlayer;		///< Pointer to the parent manager
	SimpleArray<WordPtr> m_TagStack;	///< Stack of sections marks
	Word m_uBitBucket;					///< Bit bucket for bit fields
	Word m_uBitsRemaining;				///< Number of bits in the bit bucket
public:
	Stream(const Manager *pFlashPlayer,InputMemoryStream *pInput);
	~Stream();
	BURGER_INLINE const Manager *GetManager(void) const { return m_pFlashPlayer; }
	BURGER_INLINE void ByteAlign(void) { m_uBitsRemaining = 0; }
	BURGER_INLINE InputMemoryStream* GetStream(void) const { return m_pStream; }
	BURGER_INLINE Word GetBoolean(void) { return GetWord(1); }
	Word32 BURGER_API GetEncodedU32(void);
	Word BURGER_API GetWord(Word uBitCount);
	Int BURGER_API GetInt(Word uBitCount);
	BURGER_INLINE float GetFixedAsFloat(void) { m_uBitsRemaining = 0; return FIXEDTOFLOAT(static_cast<Fixed32>(m_pStream->GetWord32())); }
	float BURGER_API GetFloat16(void);
	BURGER_INLINE float GetFloat(void) { m_uBitsRemaining = 0; return m_pStream->GetFloat(); }
	BURGER_INLINE double GetDouble(void) { m_uBitsRemaining = 0; return m_pStream->GetDouble(); }
	BURGER_INLINE Word8 GetByte(void) { m_uBitsRemaining = 0; return m_pStream->GetByte(); }
	BURGER_INLINE Int8 GetInt8(void) { m_uBitsRemaining = 0; return static_cast<Int8>(m_pStream->GetByte()); }
	BURGER_INLINE Word16 GetShort(void) { m_uBitsRemaining = 0; return m_pStream->GetShort(); }
	BURGER_INLINE Int16 GetInt16(void) { m_uBitsRemaining = 0; return static_cast<Int16>(m_pStream->GetShort()); }
	BURGER_INLINE Word32 GetWord32(void) { m_uBitsRemaining = 0; return m_pStream->GetWord32(); }
	BURGER_INLINE Int32 GetInt32(void) { m_uBitsRemaining = 0; return static_cast<Int32>(m_pStream->GetWord32()); }
	BURGER_INLINE Int32 GetEncodedInt32(void) { return static_cast<Int32>(GetEncodedU32()); }
	BURGER_INLINE Word32 GetEncodedU30(void) { return GetEncodedU32(); }
	Word BURGER_API GetVariableCount(void);
	void BURGER_API ReadString(String *pOutput);
	void BURGER_API ReadPString(String *pOutput);
	void BURGER_API ReadString(WordPtr uLength,String *pOutput);
	BURGER_INLINE WordPtr GetMark(void) const { return m_pStream->GetMark(); }
	void BURGER_API SetMark(WordPtr uMark);
	WordPtr	BURGER_API GetTagEndPosition(void) const;
	Word BURGER_API StartTag(void);
	void BURGER_API CloseTag(void);
};
}}
namespace Burger { namespace Flash {
class RGBAWord8 : public RGBAWord8_t {
public:
	RGBAWord8() {
		m_uRed = 255;
		m_uGreen = 255;
		m_uBlue = 255;
		m_uAlpha = 255;
	}
	RGBAWord8(Word8 bRed,Word8 bGreen,Word8 bBlue,Word8 bAlpha) {
		m_uRed = bRed;
		m_uGreen = bGreen;
		m_uBlue = bBlue;
		m_uAlpha = bAlpha;
	}
	RGBAWord8(double dColor) { Set(dColor); }
	void BURGER_API Read(Stream *pStream,Word uTagType);
	void BURGER_API ReadRGBA(Stream *pStream);
	void BURGER_API ReadRGB(Stream *pStream);
	BURGER_INLINE void Set(Word8 bRed,Word8 bGreen,Word8 bBlue,Word8 bAlpha) {
		m_uRed = bRed;
		m_uGreen = bGreen;
		m_uBlue = bBlue;
		m_uAlpha = bAlpha;
	}
	void BURGER_API Set(Word32 uColor);
	BURGER_INLINE void BURGER_API Set(double dColor) { Set(static_cast<Word32>(static_cast<int>(dColor))); }
	void BURGER_API Print(void) const;
};
}}
namespace Burger { namespace Flash {
class Matrix23 {
public:
	float m_fScaleX;			///< XScale value
	float m_fRotateSkew0;		///< X rotation skew
	float m_fRotateSkew1;		///< Y rotation skew
	float m_fScaleY;			///< YScale value
	float m_fTranslateX;		///< X translation
	float m_fTranslateY;		///< Y translation
	Matrix23();
	void BURGER_API Identity(void);
	void BURGER_API Concatenate(const Matrix23 *pInput);
	void BURGER_API ConcatenateTranslation(float fX,float fY);
	void BURGER_API ConcatenateScale(float fScale);
	void BURGER_API Interpolate(const Matrix23 *pInput1,const Matrix23 *pInput2,float fFactor);
	void BURGER_API SetScaleRotation(float fXScale,float fYScale,float fRotation);
	void BURGER_API Read(Stream* pStream);
	void BURGER_API Transform(Vector2D_t* pOutput,const Vector2D_t *pInput) const;
	void BURGER_API Transform(Vector2D_t* pOutput,float fX,float fY) const;
	void BURGER_API Transform(Vector4D_t* pBounds) const;
	void BURGER_API TransformVector(Vector2D_t* pOutput,const Vector2D_t *pInput) const;
	void BURGER_API TransformByInverse(Vector2D_t* pOutput,const Vector2D_t *pInput) const;
	void BURGER_API TransformByInverse(Vector4D_t* pBounds) const;
	void BURGER_API SetInverse(const Matrix23 *pInput);
	Word BURGER_API DoesFlip(void) const;
	BURGER_INLINE float GetDeterminant(void) const { return (m_fScaleX * m_fScaleY) - (m_fRotateSkew1 * m_fRotateSkew0); }
	float BURGER_API GetMaxScale(void) const;
	float BURGER_API GetXScale(void) const;
	float BURGER_API GetYScale(void) const;
	float BURGER_API GetRotation(void) const;
	void BURGER_API Print(void) const;
	Word BURGER_API operator==(const Matrix23& rInput) const;
	Word BURGER_API operator!=(const Matrix23& rInput) const;
};
}}
namespace Burger { namespace Flash {
class CharacterObject;
enum eFileType {
	UNKNOWN,		///< Unknown file
	SWF,			///< Flash file
	JPG,			///< Jpeg file format
	X3DS,			///< 3D files
	TXT,			///< Raw text file
	URL				///< Web pages (XML)
};
enum eActionScriptStandardMember {
	M_INVALID_MEMBER = -1,		///< Error in the function Burger::Flash::EnumerateStandardMember(const char *)
	M_X,				///< "_x"
	M_Y,				///< "_y"
	M_XSCALE,			///< "_xscale"
	M_YSCALE,			///< "_yscale"
	M_CURRENTFRAME,		///< "_currentframe"
	M_TOTALFRAMES,		///< "_totalframes"
	M_ALPHA,			///< "_alpha"
	M_VISIBLE,			///< "_visible"
	M_WIDTH,			///< "_width"
	M_HEIGHT,			///< "_height"
	M_ROTATION,			///< "_rotation"
	M_TARGET,			///< "_target"
	M_FRAMESLOADED,		///< "_framesloaded"
	M_NAME,				///< "_name"
	M_DROPTARGET,		///< "_droptarget"
	M_URL,				///< "_url"
	M_HIGHQUALITY,		///< "_highquality"
	M_FOCUSRECT,		///< "_focusrect"
	M_SOUNDBUFTIME,		///< "_soundbuftime"
	M_XMOUSE,			///< "_xmouse"
	M_YMOUSE,			///< "_ymouse"
	M_PARENT,			///< "_parent"
	M_TEXT,				///< "text"
	M_TEXTWIDTH,		///< "textWidth"
	M_TEXTCOLOR,		///< "textColor"
	M_BORDER,			///< "border"
	M_MULTILINE,		///< "multiline"
	M_WORDWRAP,			///< "wordWrap"
	M_TYPE,				///< "type"
	M_BACKGROUNDCOLOR,	///< "backgroundColor"
	M_THIS,				///< "_this"
	MTHIS,				///< "this"
	M_ROOT,				///< "_root"
	MDOT,				///< "."
	MDOT2,				///< ".."
	M_LEVEL0,			///< "_level0"
	M_GLOBAL,			///< "_global"
	M_ENABLED,			///< "enabled"
	M_PASSWORD,			///< "password"
	M_MOUSE_MOVE,		///< "onMouseMove"
	ACTION_SCRIPT_STANDARD_MEMBER_COUNT	///< Size of the array
};
extern const char * BURGER_API GetVersion(void);
BURGER_INLINE float TwipsToPixels(float fInput) { return fInput * (1.0f / 20.f); }
BURGER_INLINE float PixelsToTwips(float fInput) { return fInput * 20.f; }
extern void BURGER_API TwipsToPixels(Vector2D_t *pInput);
extern void BURGER_API PixelsToTwips(Vector2D_t *pInput);
extern Word32 BURGER_API TextureSizePower2(Word32 uInput);
extern WordPtr BURGER_API GetEncodedU32Length(Word32 *pOutput,const Word8 *pInput);
extern eActionScriptStandardMember BURGER_API EnumerateStandardMember(const char *pName);
extern eFileType BURGER_API GetFileType(const char *pFilename);
extern void BURGER_API GetFullURL(Filename *pOutput,const Filename *pDirectory,const char *pInput);
class Multiname {
public:
	enum eKind {
		CONSTANT_UNDEFINED = 0x00,	///< Uninitialized data
		CONSTANT_QName = 0x07,		///< QName object
		CONSTANT_QNameA = 0x0D,		///< QName object for attributes
		CONSTANT_RTQName = 0x0F,	///< RTQName object
		CONSTANT_RTQNameA = 0x10,	///< RTQName object for attributes
		CONSTANT_RTQNameL = 0x11,	///< RTQName object for local data
		CONSTANT_RTQNameLA = 0x12,	///< RTQName object for local attributes
		CONSTANT_Multiname = 0x09,	///< Multiname object for namespace
		CONSTANT_MultinameA = 0x0E,	///< Multiname object for attribute namespace
		CONSTANT_MultinameL = 0x1B,	///< Multiname object for local namespace
		CONSTANT_MultinameLA = 0x1C	///< Multiname object for local attribute namespace
	};
	eKind m_eKind;			///< Type of multiname structures
	Word32 m_uNS;			///< Namespace index used for QName
	Word32 m_uNS_Set;		///< Index into a Namespace set used for Multiname
	Word32 m_uName;			///< Index into the string array for the name used for QName and RTQName
	Multiname() :
		m_eKind(CONSTANT_UNDEFINED),
		m_uNS(0),
		m_uNS_Set(0),
		m_uName(0)
	{
	}
	BURGER_INLINE Word IsQName(void) const { return m_eKind == CONSTANT_QName; }
};
class Namespace {
public:
	enum eKind {
		CONSTANT_Undefined = 0x00,		///< Uninitialized data
		CONSTANT_Namespace = 0x08,		///< Global namespace
		CONSTANT_PackageNamespace = 0x16,	///< Namespace for a package
		CONSTANT_PackageInternalNs = 0x17,	///< Namespace private to a package
		CONSTANT_ProtectedNamespace = 0x18,	///< Namespace protected for a package
		CONSTANT_ExplicitNamespace = 0x19,	///< Specific namespace (Fully qualified)
		CONSTANT_StaticProtectedNs = 0x1A,	///< Global protected namespace
		CONSTANT_PrivateNs = 0x05			///< Global private namespace
	};
	eKind m_eKind;	///< Type of namespace this name represents
	Word32 m_uName;	///< Index into the string array for the name
	Namespace() :
		m_eKind(CONSTANT_Undefined),
		m_uName(0)
	{
	}
};
class BaseExecute : public Base {
	BURGER_RTTI_IN_CLASS();
public:
	BaseExecute() {}
	virtual ~BaseExecute();
	virtual void Execute(CharacterObject *pObject);
	virtual void ExecuteState(CharacterObject *pObject);
	virtual void ExecuteStateReverse(CharacterObject *pObject,Word uFrame);
	virtual Word32 GetDepthIDOfReplaceOrAddTag(void) const;
};
}}
namespace Burger { namespace Flash {
class Rect : public Vector4D_t {
public:
	Rect() {
		Zero();
	}
	void BURGER_API Read(Stream* pStream);
	Word BURGER_API IsIntersecting(const Vector4D_t *pRect) const;
	void BURGER_API SetRect(const Matrix23 *pMatrix,const Vector4D_t *pRect);
	void BURGER_API TwipsToPixels(void);
	void BURGER_API PixelsToTwips(void);
	void BURGER_API Print(void) const;
};
}}
namespace Burger { namespace Flash {
class ColorTransform {
public:
	float m_fRedMultTerm;		///< Red scale value 0.0f to 1.0f
	float m_fGreenMultTerm;		///< Green scale value 0.0f to 1.0f
	float m_fBlueMultTerm;		///< Blue scale value 0.0f to 1.0f
	float m_fAlphaMultTerm;		///< Alpha scale value 0.0f to 1.0f
	float m_fRedAddTerm;		///< Red add value -255.0f to 255.0f
	float m_fGreenAddTerm;		///< Green add value -255.0f to 255.0f
	float m_fBlueAddTerm;		///< Blue add value -255.0f to 255.0f
	float m_fAlphaAddTerm;		///< Alpha add value -255.0f to 255.0f
	ColorTransform();
	void BURGER_API Identity(void);
	void BURGER_API Concatenate(const ColorTransform *pInput);
	void BURGER_API Transform(RGBAWord8_t *pOutput,const RGBAWord8_t *pInput) const;
	void BURGER_API ReadRGB(Stream* pStream);
	void BURGER_API ReadRGBA(Stream* pStream);
	void BURGER_API Clamp(void);
	void BURGER_API Print(void) const;
};
}}
namespace Burger { namespace Flash {
extern WordPtr BURGER_API DisassembleActionScript(const Word8* pInput);
}}
namespace Burger { namespace Flash {
class SharedBuffer : public ReferenceCounter {
	SimpleArray<Word8> m_Buffer;		///< Internal data buffer
	BURGER_RTTI_IN_CLASS();
public:
	SharedBuffer();
	~SharedBuffer();
	BURGER_INLINE WordPtr GetDataSize(void) const { return m_Buffer.size();}
	BURGER_INLINE void Append(Word8 uInput) { m_Buffer.push_back(uInput); }
	BURGER_INLINE const Word8 *GetData(void) const { return &m_Buffer[0]; }
	BURGER_INLINE SimpleArray<Word8> *GetBuffer(void) { return &m_Buffer; }
};
}}
namespace Burger { namespace Flash {
class CharacterObject;
class FunctionCallParms;
class RootObject;
class ActionScriptObject;
typedef Word (BURGER_API *FSCommandProc)(CharacterObject *pMovie,const char *pCommand,const char *pArgs);		///< Function prototype for user supplied FSCommand function
typedef void (BURGER_API *ActionScriptCFunctionProc)(const FunctionCallParms *pParms);				///< Function prototype to implement an ActionScript command
class Manager {
	BURGER_DISABLECOPYCONSTRUCTORS(Manager);
	GameApp *m_pGameApp;				///< Pointer to the application instance
	FSCommandProc m_pFSCommmand;		///< Callback for FSCommand support
	WeakPointer<RootObject> m_pCurrentObject;
	float m_fTextureLODBias;			///< Texture Level of detail bias
	float m_fCurvePixelError;			///< Allowable error on generating curves. Higher numbers means coarser curves.
	Word m_bUseRealtimeFrameRateFlag;	///< Set to \ref TRUE if flash logic MUST be called once per frame in slow situations
	Word m_bVerboseActionFlag;			///< Print debug messages for Action Script
	Word m_bVerboseParsingFlag;			///< Print debug messages for data parsing
	Word m_bVerboseBitmapInfoFlag;		///< Print debug messages for bitmap information
	Word m_bAllowMultithreadingFlag;	///< \ref TRUE if multithreading is allowed
	Random m_Random;					///< Random number generator instance
	Filename m_BaseDirectory;			///< Directory to load files from
	HashMapString<CodeLibrary*> m_CodeLibraryHash;		///< Hash of code libraries and pointers to their data
	String m_GlobalEnvironmentVariables;	///< A list of environment variables to pass to all Flash movies
	const String m_ConstructorName;		///< "__constructor__" global for internal use
	CriticalSection m_CriticalSection;	///< Critical section for the flash player
public:
	Manager(GameApp *pApp);
	~Manager();
	BURGER_INLINE GameApp *GetGameApp(void) const { return m_pGameApp; }
	BURGER_INLINE FSCommandProc GetFSCallback(void) const { return m_pFSCommmand; }
	BURGER_INLINE void SetFSCallback(FSCommandProc pFSCommand) { m_pFSCommmand = pFSCommand; }
	BURGER_INLINE RootObject* GetRootObject(void) const { return m_pCurrentObject.GetPtr(); }
	void BURGER_API SetRootObject(RootObject *pObject);
	BURGER_INLINE Random *GetRandomGenerator(void) { return &m_Random; }
	BURGER_INLINE Filename *GetDataDirectory(void) { return &m_BaseDirectory; }
	BURGER_INLINE void SetDataDirectory(const char *pDirectory) { m_BaseDirectory.Set(pDirectory); }
	BURGER_INLINE float GetLODBias(void) const { return m_fTextureLODBias; }
	void BURGER_API SetLODBias(float fTextureLODBias=-1.2f);
	BURGER_INLINE float GetCurvePixelError(void) const { return m_fCurvePixelError; }
	void BURGER_API SetCurvePixelError(float fCurvePixelError=1.0f);
	BURGER_INLINE Word GetRealtimeFrameRateFlag(void) const { return m_bUseRealtimeFrameRateFlag; }
	BURGER_INLINE void SetRealtimeFrameRateFlag(Word bUseRealtimeFrameRateFlag) { m_bUseRealtimeFrameRateFlag = bUseRealtimeFrameRateFlag; }
	BURGER_INLINE Word GetVerboseActionFlag(void) const { return m_bVerboseActionFlag; }
	BURGER_INLINE void SetVerboseActionFlag(Word bVerboseActionFlag) { m_bVerboseActionFlag = bVerboseActionFlag; }
	BURGER_INLINE Word GetVerboseParsingFlag(void) const { return m_bVerboseParsingFlag; }
	BURGER_INLINE void SetVerboseParsingFlag(Word bVerboseParsingFlag) { m_bVerboseParsingFlag = bVerboseParsingFlag; }
	BURGER_INLINE Word GetVerboseBitmapInfoFlag(void) const { return m_bVerboseBitmapInfoFlag; }
	BURGER_INLINE void SetVerboseBitmapInfoFlag(Word bVerboseBitmapInfoFlag) { m_bVerboseBitmapInfoFlag = bVerboseBitmapInfoFlag; }
	BURGER_INLINE Word GetAllowMultithreadingFlag(void) const { return m_bAllowMultithreadingFlag; }
	BURGER_INLINE void SetAllowMultithreadingFlag(Word bAllowMultithreadingFlag) { m_bAllowMultithreadingFlag = bAllowMultithreadingFlag; }
	CodeLibrary * BURGER_API LoadCodeLibrary(const String *pName);
	void BURGER_API ReleaseCodeLibraries(void);
	BURGER_INLINE const String *GetGlobalEnvironmentVariables(void) const { return &m_GlobalEnvironmentVariables; }
	void BURGER_API SetGlobalEnvironmentVariables(const char *pInput);
	BURGER_INLINE const String *GetConstructorName(void) const { return &m_ConstructorName; }
	BURGER_INLINE void Lock(void) { m_CriticalSection.Lock(); }
	BURGER_INLINE void Unlock(void) { m_CriticalSection.Unlock(); }
};
}}
namespace Burger { namespace Flash {
class ActionScriptFunction;
class ActionScriptObject;
class ActionScriptValue;
class OldFlashManager;
class ActionScriptSFunction;
class ActionScriptProperty : public WeakAndStrongBase {
	SmartPointer<ActionScriptFunction> m_GetFunction;		///< Function object to call when data is to be retrieved
	SmartPointer<ActionScriptFunction> m_SetFunction;		///< Function object to call when data is being updated
	BURGER_RTTI_IN_CLASS();
public:
	ActionScriptProperty(const ActionScriptValue &rGetFunction,const ActionScriptValue &rSetFunction);
	virtual ~ActionScriptProperty();
	void SetFunction(ActionScriptObject *pTargetObject,const ActionScriptValue &rValue);
	void GetFunction(ActionScriptObject *pTargetObject,ActionScriptValue *pValue) const;
	void GetFunction(const ActionScriptValue &rTargetObject,ActionScriptValue *pValue) const;
	void Print(void) const;
};
class ActionScriptValue {
public:
	enum eValueFlag {
		DONT_ENUM = 0x01,
		DONT_DELETE = 0x02,
		READ_ONLY = 0x04
	};
private:
	enum eType {
		UNDEFINED,
		BOOLEAN,
		NUMBER,
		STRING,
		OBJECT,
		PROPERTY
	};
	SmartPointer<ActionScriptObject> m_pObject;	///< Object that this variable belongs to
	SmartPointer<ActionScriptObject> m_pPropertyTarget;	///< Property target for this variable
	SmartPointer<ActionScriptProperty> m_pProperty;		///< Property for this variable
	mutable String m_String;	///< String variable
	double m_dNumber;			///< Numeric value (As double)
	Word m_bBool;				///< Boolean value
	eType m_eType;				///< Type of data contained
	mutable Word m_uFlags;		///< eValueFlag flags
public:
	ActionScriptValue();
	ActionScriptValue(const ActionScriptValue &rInput);
	ActionScriptValue(const char *pInput);
	ActionScriptValue(bool bInput);
	ActionScriptValue(int iInput);
	ActionScriptValue(float fInput);
	ActionScriptValue(double dInput);
	ActionScriptValue(ActionScriptObject* pObject);
	ActionScriptValue(Manager *pManager,ActionScriptCFunctionProc pProc);
	ActionScriptValue(ActionScriptSFunction *pInput);
	ActionScriptValue(const ActionScriptValue &rGetFunction,const ActionScriptValue &rSetFunction);
	~ActionScriptValue();
	void ReleaseReferences(void);
	const char *ToDebugString(void) const;
	const char *ToCharPtr(void) const;
	const String &ToString(void) const;
	double ToDouble(void) const;
	int ToInt(void) const { return (int) ToDouble(); };
	float ToFloat(void) const { return (float) ToDouble(); };
	Word ToBool(void) const;
	ActionScriptFunction* CastToFunction(void) const;
	ActionScriptObject* CastToObject(void) const;
	ActionScriptProperty* CastToProperty(void) const;
	void SetString(const String &rInput);
	void SetString(const char *pInput);
	void SetDouble(double dInput);
	void SetBool(Word bInput);
	void SetInt(int iInput) { SetDouble(static_cast<double>(iInput)); }
	void SetNaN(void) { SetDouble(g_dNan); }
	void SetAsObject(ActionScriptObject *pObject);
	void SetAsCFunction(Manager *pManager,ActionScriptCFunctionProc pProc);
	void SetUndefined(void);
	void SetNULL(void) { SetAsObject(NULL); }
	void SetProperty(const ActionScriptValue &rInput);
	void GetProperty(ActionScriptValue *pScript) const;
	void GetProperty(const ActionScriptValue &rInput,ActionScriptValue *pScript) const;
	const ActionScriptObject *GetPropertyTarget(void) const;
	void SetPropertyTarget(ActionScriptObject *pObject);
	void operator=(const ActionScriptValue &rInput);
	Word operator==(const ActionScriptValue &rInput) const;
	Word operator!=(const ActionScriptValue &rInput) const;
	Word operator<(double dInput) const { return ToDouble() < dInput; }
	void operator+=(double dInput) { SetDouble(ToDouble() + dInput); }
	void operator-=(double dInput) { SetDouble(ToDouble() - dInput); }
	void operator*=(double dInput) { SetDouble(ToDouble() * dInput); }
	void operator/=(double dInput) { SetDouble(ToDouble() / dInput); }
	void operator&=(int iInput) { SetInt(int(ToDouble()) & iInput); }
	void operator|=(int iInput) { SetInt(int(ToDouble()) | iInput); }
	void operator^=(int iInput) { SetInt(int(ToDouble()) ^ iInput); }
	void shl(int iInput) { SetInt(int(ToDouble()) << iInput); }
	void asr(int iInput) { SetInt(int(ToDouble()) >> iInput); }
	void lsr(int iInput) { SetInt(static_cast<int>((Word32(ToDouble()) >> iInput))); }
	Word IsFunction(void) const;
	BURGER_INLINE Word IsBool(void) const { return m_eType == BOOLEAN; }
	BURGER_INLINE Word IsString(void) const { return m_eType == STRING; }
	BURGER_INLINE Word IsNumber(void) const { return m_eType == NUMBER && IsNan(m_dNumber) == false; }
	BURGER_INLINE Word IsObject(void) const { return m_eType == OBJECT; }
	BURGER_INLINE Word IsProperty(void) const { return m_eType == PROPERTY; }
	BURGER_INLINE Word IsNULL(void) const { return m_eType == OBJECT && m_pObject == NULL; }
	BURGER_INLINE Word IsUndefined(void) const { return m_eType == UNDEFINED; }
	const char* GetTypeOf(void) const;
	Word IsInstanceOf(const ActionScriptFunction *pFunction) const;
	Word FindProperty(const String &rInput,ActionScriptValue *pValue);
	Word FindPropertyOwner(const String &rInput,ActionScriptValue *pValue);
	BURGER_INLINE Word IsEnum(void) const { return static_cast<Word>(m_uFlags & DONT_ENUM ? FALSE : TRUE); }
	BURGER_INLINE Word IsReadOnly(void) const { return static_cast<Word>(m_uFlags & READ_ONLY ? TRUE : FALSE); }
	BURGER_INLINE Word IsProtected(void) const { return static_cast<Word>(m_uFlags & DONT_DELETE ? TRUE : FALSE); }
	BURGER_INLINE Word GetFlags(void) const { return m_uFlags; }
	BURGER_INLINE void SetFlags(Word flags) const  { m_uFlags = flags; }
	static Word CompareEqual(const ActionScriptValue &rInput1,const ActionScriptValue &rInput2);
	static ActionScriptValue RelationalCompareEqual(const ActionScriptValue &rInput1,const ActionScriptValue &rInput2);
};
}}
namespace Burger { namespace Flash {
class ABC_Definition;
struct OptionDetail_t {
	enum eKind {
		CONSTANT_Undefined=0x00,		///< Unused
		CONSTANT_Utf8=0x01,				///< UTF8 string
		CONSTANT_Int=0x03,				///< Signed 32 bit integer
		CONSTANT_UInt=0x04,				///< Unsigned 32 bit integer
		CONSTANT_PrivateNs=0x05,		///< Private namespace to the class
		CONSTANT_Double=0x06,			///< 64 bit floating point
		CONSTANT_Namespace=0x08,		///< Global namespace
		CONSTANT_False=0x0A,			///< Boolean \ref FALSE
		CONSTANT_True=0x0B,				///< Boolean \ref TRUE
		CONSTANT_Null=0x0C,				///< \ref NULL pointer
		CONSTANT_PackageNamespace=0x16,	///< Namespace exclusive to the package
		CONSTANT_PackageInternalNs=0x17,	///< Local package namespace
		CONSTANT_ProtectedNamespace=0x18,	///< Protected namespace
		CONSTANT_ExplicitNamespace=0x19,	///< Explicit namespace
		CONSTANT_StaticProtectedNs=0x1A		///< Static protected namespace
	};
	Word32 m_uValue;			///< Index into the constant pool
	eKind m_eKind;				///< Type of variable found in the constant pool
	void BURGER_API Read(Stream *pStream);
};
struct ItemInfo_t {
	Word m_uKey;			///< Key value
	Word m_uValue;			///< Value attached to the key
	void BURGER_API Read(Stream* pStream);
};
class TraitsInfo : public WeakAndStrongBase {
public:
	enum eKind {
		Trait_Slot = 0,		///< Data is found in trait_slot
		Trait_Method = 1,	///< Data is found in trait_method
		Trait_Getter = 2,	///< Data is found in trait_method
		Trait_Setter = 3,	///< Data is found in trait_method
		Trait_Class = 4,	///< Data is found in trait_class
		Trait_Function = 5,	///< Data is found in trait_function
		Trait_Const = 6,	///< Data is found in trait_slot
		Trait_Invalid = 255	///< Invalid record
	};
	enum eAttribute {
		ATTR_Final = 0x1,	///< Is used with Trait_Method, Trait_Getter and Trait_Setter. It marks a method that cannot be overridden by a sub-class
		ATTR_Override = 0x2,///< Is used with Trait_Method, Trait_Getter and Trait_Setter. It marks a method that has been overridden in this class
		ATTR_Metadata = 0x4	///< Is used to signal that the fields metadata_count and metadata follow the data field in the traits_info entry
	};
	int m_uName;			///< Index to the multiname constant pool
	eKind m_eKind;			///< Specific kind of data contained in this class
	Word m_eAttribute;		///< Attributes for how to handle overrides
	union {
		struct {
			Word m_uSlotID;		///< Position identification for this trait
			Word m_uTypeName;	///< Index into the multiname array for this item's name
			Word m_uVIndex;		///< Index into the constant pool for this data
			Flash::OptionDetail_t::eKind m_eKind;	///< Kind of data in the constant pool
		} trait_slot;			///< Used by eKind \ref Trait_Slot and \ref Trait_Const
		struct {
			Word m_uSlotID;		///< Position identification for this trait
			Word m_uClassIndex;	///< Index into the class array
		} trait_class;			///< Used by eKind \ref Trait_Class
		struct {
			Word m_uSlotID;		///< Position identification for this trait
			Word m_uFunction;	///< Index into the function array
		} trait_function;		///< Used by eKind \ref Trait_Function
		struct {
			Word m_uDispatchID;	///< Index into the dispatcher array
			Word m_uMethodIndex;	///< Index into the method array
		} trait_method;			///< Used by eKind \ref Trait_Method, \ref Trait_Getter or \ref Trait_Setter
	};
	SimpleArray<Word> m_uMetadataArray;	///< Array of indexes into the metadata array
	TraitsInfo();
	~TraitsInfo();
	void BURGER_API Read(Stream *pStream,ABC_Definition *pABCDefinition);
};
class MetadataInfo : public WeakAndStrongBase {
public:
	Word m_uName;									///< Name index into the string array
	SimpleArray<ItemInfo_t> m_ItemInfoArray;		///< Array of key / value pairs
	MetadataInfo();
	~MetadataInfo();
	void BURGER_API Read(Stream* pStream);
};
class ExceptionInfo : public WeakAndStrongBase {
public:
	Word m_uFrom;		///< The starting position in the code field from which the exception is enabled.
	Word m_uTo;			///< The ending position in the code field after which the exception is disabled.
	Word m_uTarget;		///< The position in the code field to which control should jump if an exception of type exc_type is encountered
	Word m_uExceptionType;	///< An index into the string array of the constant pool that identifies the name of the type of exception
	Word m_uVariableName;	///< This index into the string array of the constant pool defines the name of the variable that is to receive the exception object
	ExceptionInfo();
	~ExceptionInfo();
	void BURGER_API Read(Stream* pStream);
};
class InstanceInfo : public WeakAndStrongBase {
public:
	enum eFlags {
		CONSTANT_ClassSealed = 0x01,	///< The class is sealed: properties can not be dynamically added to instances of the class.
		CONSTANT_ClassFinal = 0x02,		///< The class is final: it cannot be a base class for any other class.
		CONSTANT_ClassInterface = 0x04,	///< The class is an interface.
		CONSTANT_ClassProtectedNs = 0x08	///< The class uses its protected namespace and the m_uProtectedNamespace field is present in the InstanceInfo class.
	};
	WeakPointer<ABC_Definition> m_pParentABCDefinition;		///< Parent Adobe Byte Code
	SimpleArray<Word> m_uInterfaceArray;								///< Array of interface indexes
	ClassArray<SmartPointer<TraitsInfo> > m_pTraitArray;				///< Array of instance traits
	Word m_uName;				///< Name of this instance
	Word m_uSuperName;			///< Name of the parent class this derives from
	Word m_uFlags;				///< See \ref eFlags
	Word m_uProtectedNamespace;	///< If protected, this contains the index to the protected namespace
	Word m_uInitializationIndex;	///< Index to the initialization function
	InstanceInfo();
	~InstanceInfo();
	void BURGER_API Read(Stream *pStream,ABC_Definition *pABCDefinition);
};
class ClassInfo : public WeakAndStrongBase {
public:
	WeakPointer<ABC_Definition> m_pParentABCDefinition;
	ClassArray<SmartPointer<TraitsInfo> > m_pTraitArray;
	Word m_uClassInit;
	ClassInfo();
	~ClassInfo();
	void BURGER_API Read(Stream* pStream,ABC_Definition *pABCDefinition);
};
class ScriptInfo : public WeakAndStrongBase {
public:
	ClassArray<SmartPointer<TraitsInfo> > m_pTraitArray;
	Word m_uScriptInit;
	ScriptInfo();
	~ScriptInfo();
	void BURGER_API Read(Stream* pStream,ABC_Definition *pABCDefinition);
};
}}

#if defined(__MWERKS__)
#pragma ANSI_strict reset
#pragma enumsalwaysint reset
#endif

#if defined(BURGER_STRUCT_ALIGN)
#pragma options align=reset
#elif defined(BURGER_STRUCT_PACKPUSH)
#pragma pack(pop)
#elif defined(BURGER_STRUCT_PACK)
#pragma pack()
#endif

#if !defined(BURGER_NO_USING_NAMESPACE)
using namespace Burger;
#endif

#endif
