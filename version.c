/* VERSION.C    (c) Copyright Roger Bowler, 1999-2012                */
/*              Hercules Version Display Module                      */
/*                                                                   */
/*   Released under "The Q Public License Version 1"                 */
/*   (http://www.hercules-390.org/herclic.html) as modifications to  */
/*   Hercules.                                                       */

/*-------------------------------------------------------------------*/
/* This module displays the Hercules program name and version,       */
/* copyright notice, build date and time, and build information.     */
/*-------------------------------------------------------------------*/

#include "hstdinc.h"

#define _VERSION_C_
#define _HUTIL_DLL_

#include "hercules.h"
#include "machdep.h"

/*--------------------------------------------------*/
/*   "Unusual" (i.e. noteworthy) build options...   */
/*--------------------------------------------------*/

static const char *build_info[] = {

/*  Report custom build information provided by invoker through
 *  ./configure process.
 */

#if defined(CUSTOM_BUILD_STRING)
    CUSTOM_BUILD_STRING,
#endif


/*  Report compiler environment
 *
 *  The build process, when able, can set
 *  CONFIGURE_COMPILER_VERSION_STRING to the desired value for reporting
 *  purposes, and not rely on the partial information that the compilers
 *  offer via predefined macro values.
 *
 *  Predefined macro values for individual compilers is documented at
 *  http://sourceforge.net/p/predef/wiki/Compilers/.
 *
 *  +------------------------------------------------------------------+
 *  |   CAUTION                                                        |
 *  |   -------                                                        |
 *  |   The specification of any compiler here is not to be            |
 *  |   construed as being supported by Hercules or that the           |
 *  |   compiler can be successfully used to compile Hercules.         |
 *  +------------------------------------------------------------------+
 *
 */

#define __string(s)     #s
#define __defer(m, ...) m(__VA_ARGS__)
#define value(s)        __defer(__string, s)

#if defined(CONFIGURE_COMPILER_VERSION_STRING)
    CONFIGURE_COMPILER_VERSION_STRING,
#elif defined(_ACC_)
    "ACC",
#elif defined(_CMB_)
    "Altium MicroBlaze C " value(__VERSION__)
    #if defined(__REVISION__)
        " Patch " value(__REVISION__)
    #endif
    ,   /* Don't forget the comma to keep the compiler happy! */
#elif defined(__CHC__)
    "Altium C-to-Hardware " value(__VERSION)
    #if defined(__REVISION__)
        " Patch " value(__REVISION__)
    #endif
    ,   /* Don't forget the comma to keep the compiler happy! */
#elif defined(__ACK__)
    "Amsterdam Compiler Kit",
#elif defined(__CC_ARM)
    "ARM Compiler " __ARMCC_VERSION,
#elif defined(AZTEC_C) || defined(__AZTEC_C__)
    "Aztec C " value(__VERSION),
#elif defined(__CC65__)
    "CC65 " value(__CC65__),
#elif defined(__clang__)
    #if defined(__apple_build_version__)
        "Apple "
    #endif
    "Clang " __clang_version__,
#elif defined(__DECC)
    "Compaq C " value(__DECC_VER),
#elif defined(__convexc__)
    "Convex C",
#elif defined(__COMPCERT__)
    "CompCert",
#elif defined(__COVERITY__)
    "Coverity C Static Analyzer",
#elif defined(__DCC__)
    "Diab C " value(__VERSION_NUMBER__),
#elif defined(_DICE)
    "DICE C",
#elif defined(__DMC__)
    "Digital Mars " value(__DMC__),
#elif defined(__SYSC__)
    "Dignus Systems/C " value(__SYSC_VER__),
#elif defined(__DJGPP__)
    "DJGPP " __DJGPP__ "." __DJGPP_MINOR__,
#elif defined(__PATHCC__)
    "EKOPATH " value(__PATHCC__) "." value(__PATHCC_MINOR__)
    #if defined(__PATHCC_PATCHLEVEL__)
         "." value(__PATHCC_PATCHLEVEL__)
    #endif
    ,   /* Don't forget the comma to keep the compiler happy! */
#elif defined(__ghs__)
    "Green Hill C " value(__GHS_VERSION_NUMBER__)
                " " value(__GHS_REVISION_DATE__),
#elif defined(__IAR_SYSTEMS_ICC__)
    "IAR C " __VER__,
#elif defined(__xlc__) || defined(__xlC__) || defined(__IBMC__)
    "IBM "
    #if defined(__MVS__) || defined(__COMPILER_VER__)
        "z/OS C "
    #else
        "XL C "
    #endif
    value(__IBMC__),
#elif defined(__INTEL_COMPILER) || defined(__ICC) ||                    \
      defined(_ECC) || defined(_ICL)
    "Intel C " value(__INTEL_COMPILER)
           " " value(__INTEL_COMPILER_BUILD_DATE),
#elif defined(__IMAGECRAFT__)
    "ImageCraft C",
#elif defined(__KEIL__)
    "KEIL CARM " value(__CA__),
#elif defined(__C166__)
    "KEIL C166",
#elif defined(__C51__)
    "KEIL C51",
#elif defined(__LCC__)
    "LCC",
#elif defined(__llvm__)
    "LLVM",
#elif defined(__HIGHC__)
    "MetaWare High C",
#elif defined(__MWERKS__)
    "Metrowerks CodeWarrior",
#elif defined(__MSC_VER)
    "Microsoft Visual C " value(_MSC_FULL_VER)
    #if defined(_MSC_BUILD)
        " " value(_MSC_BUILD)
    #endif
    ,   /* Don't forget the comma to keep the compiler happy! */
#elif defined(_MRI)
    "Microtec C",
#elif defined(__NDPC__) || defined(__NDPX__)
    "Microway NDP C",
#elif defined(__sgi)
    "MIPSpro "
    #if defined(_COMPILER_VERSION)
        value(_COMPILER_VERSION)
    #else
        value(_SGI_COMPILER_VERSION)
    #endif
    ,   /* Don't forget the comma to keep the compiler happy! */
#elif defined(MIRACLE)
    "Miracle C",
#elif defined(__CC_NORCROFT)
    "Norcroft C",   /* __ARMCC_VERSION is a floating-point number */
#elif defined(__NWCC__)
    "NWCC",
#elif defined(__OPEN64__) || defined(__OPENCC__)
    "Open64 "
    #if defined(__OPEN64__)
        __OPEN64__
    #else
        value(__OPENCC__)
        "." value(__OPENCC_MINOR__)
        /* __OPENCC_PATCHLEVEL__ is a floating-point number */
    #endif
    ,   /* Don't forget the comma to keep the compiler happy! */
#elif defined(__SUNPRO_C)
    "Oracle Solaris Studio",
#elif defined(__PACIFIC__)
    "Pacific C",
#elif defined(_PACC_VER)
    "Palm C",
#elif defined(__POCC__)
    "Pelles C",
#elif defined(__PGI)
    "Portland Group C " value(__PGIC__)
                    "." value(__PGIC_MINOR__)
    #if defined(__PGIC_PATCHLEVEL__) && __PGIC_PATCHLEVEL__ > 0
                    "." value(__PGIC_PATCHLEVEL__)
    #endif
    ,   /* Don't forget the comma to keep the compiler happy! */
#elif defined(__RENESAS__) || defined(__HITACHI__)
    #if defined(__RENESAS__)
        "Renesas C " value(__RENESAS_VERSION__)
    #else
        "Hitachi C " value(__HITACHI_VERSION__)
    #endif
    ,   /* Don't forget the comma to keep the compiler happy! */
#elif defined(SASC) || defined(__SASC) || defined(__SASC__)
    "SAS/C "
    #if defined(__VERSION__) && defined(__REVISION__)
        value(__VERSION__) "." value(__REVISION__)
    #else
        value(__SASC__)
    #endif
    ,   /* Don't forget the comma to keep the compiler happy! */
#elif defined(_SCO_DS)
    "SCO OpenServer",
#elif defined(SDCC)
    "Small Device C Compiler " value(SDCC),
#elif defined(__SNC__)
    "SN Compiler",
#elif defined(__VOSC__)
    "Stratus VOS "
    #if __VOSC__
        "K&R"
    #else
        "ANSI"
    #endif
    " C Compiler",
#elif defined(__TenDRA__)
    "TenDRA C",
#elif defined(__TI_COMPILER_VERSION__)
    "Texas Instruments C Compiler" value(__TI_COMPILER_VERSION),
#elif defined(THINKC3) || defined(THINKC4)
    "THINK C Version "
    #if defined(THINKC3)
        "3"
    #else
        "4"
    #endif
    ".x",
#elif defined(__TINYC__)
    "Tiny C",
#elif defined(__TURBOC__)
    "Turbo C " value(__TURBOC__),
#elif defined(_UCC)
    "Ultimate C " value(_MAJOR_REV) "." value(_MINOR_REV),
#elif defined(__USLC__)
    "USL C " value(__SCO_VERSION__),
#elif defined(__VBCC__)
    "VBCC",
#elif defined(__GNUC__)
    /*
     * This must be the last test due to "GCC compliant" compilers from
     * other vendors.
     */
    "GCC " __VERSION__,
#else
    /* Unknown compiler in use... */
#endif


/*  Report toolchain
 *
 *  The build process, when able, can set
 *  CONFIGURE_TOOLCHAIN_VERSION_STRING to the desired value for
 *  purposes, and not rely on the partial information that the compilers
 *  toolchain reporting offer via predefined macro values.
 *
 */

#if defined(CONFIGURE_TOOLCHAIN_VERSION_STRING)
    CONFIGURE_TOOLCHAIN_VERSION_STRING,
#elif defined(__MINGW32__) || defined(__MINGW64__)
    "MinGW "
    #if defined(__MINGW32__)
        "32-bit " value(__MINGW32_MAJOR_VERSION__)
              "." value(__MINGW32_MINOR_VERSION__)
    #else
        "64-bit " value(__MINGW64_VERSION_MAJOR__)
              "." value(__MINGW64_VERSION_MINOR__)
    #endif
    ,   /* Don't forget the comma to keep the compiler happy! */
#else
    /* Unknown toolchain in use... */
#endif


/* Report Host Environment */

#if !defined(HOST_ARCH)
  #error HOST_ARCH is undefined
#endif

#if defined(_MSVC_)
  #define QSTR_HOST_ARCH    QSTR(HOST_ARCH)
#else
  #define QSTR_HOST_ARCH         HOST_ARCH
#endif

#if   defined(_AIX)
    "AIX"
#elif defined(__ANDROID__)
    "Android"
    #if defined(__ANDROID_API__)
        value(__ANDROID_API__)
    #endif
#elif defined(UTS)
    "Amdahl UTS"
#elif defined(AMIGA) || defined(__amigaos__)
    "AmigaOS"
#elif defined(aegis)
    "Apollo AEGIS"
#elif defined(apollo)
    "Apollo Domain/OS"
#elif defined(__OS__)
    "BeOS"
#elif defined(__bg__) || defined(__THW_BLUEGENE__)
    "Blue Gene"
    #if defined(__bgq__) || defined(__TOS_BGQ__)
        "/Q"
    #endif
#elif defined(__FREEBSD__)                                          ||  \
      defined(__NetBSD__)                                           ||  \
      defined(__OpenBSD__)                                          ||  \
      defined(__bsdi__)                                             ||  \
      defined(__DragonFly__)
    #if defined(__FREEBSD__)
        "Free"
    #elif defined(__NetBSD__)
        "Net"
    #elif defined(__OpenBSD__)
        "Open"
    #elif defined(__DragonFly__)
        "DragonFly "
    #endif
    "BSD"
    #if defined(__bsdi__)
        "/OS"
    #endif
    #if   defined(BSD)
        " " value(BSD)
    #elif defined(__FreeBSD_version)
        " " value(__FreeBSD_version)
    #elif defined(__FreeBSD__)
        " " value(__FreeBSD__)
    #elif defined(__NetBSD_Version__)
        " " value(__NetBSD_Version__)
    #endif
#elif defined(__convex__)
    "ConvexOS"
#elif defined(__CYGWIN__)
    "Cygwin Environment"
#elif defined(__dgux__) || defined(__DGUX__)
    "DG/UX"
#elif defined(_SEQUENT_) || defined(sequent)
    "DYNIX/ptx"
#elif defined(_ECOS)
    "eCos"
#elif defined(__EMX__)
    "EMX Environment"
#elif defined(__gnu_hurd__)
    "GNU/Hurd"
#elif defined(__FreeBSD_kernel__) && defined(__GLIBC__)
    "GNU/kFreeBSD"
#elif defined(__gnu_linux__)
    "GNU/Linux"
#elif defined(_hpux) || defined(hpux) || defined(__hpux)
    "HP-UX"
#elif defined(__OS400__)
    "IBM OS/400"
#elif defined(__INTEGRITY)
    "INTEGRITY"
#elif defined(__INTERIX)
    "Interix Environment"
#elif defined(sgi) || defined(__sgi)
    "IRIX"
#elif defined(__Lynx__)
    "LynxOS"
#elif defined(macintosh) || defined(Macintosh) ||                       \
      (defined(__APPLE__) && defined(__MACH__))
    "Mac OS "
    #if defined(macintosh) || defined(Macintosh)
        "9"
    #else
        "X"
    #endif
#elif defined(__OS9000) || defined(_OSK)
    "Microware OS-9"
#elif defined(__minix)
    "MINIX"
#elif defined(__MORPHOS__)
    "MorphOS"
#elif defined(mpeix) || defined(__mpexl)
    "MPE/iX"
#elif defined(MSDOS) || defined(__MSDOS__) || defined(_MSDOS) ||        \
      defined(__DOS__)
    "MSDOS"
#elif defined(__TANDEM)
    "Tandem NonStop"
#elif defined(__nucleus__)
    "Nucleus RTOS"
#elif defined(OS2) || defined(_OS2) || defined(__OS2__) ||              \
      defined(__TOS_OS2__)
    "OS/2"
#elif defined(__palmos__)
    "Palm OS"
#elif defined(EPLAN9)
    "Plan 9"
#elif defined(pyr)
    "Pyramid DC/OSx"
#elif defined(__QNX__) || defined(__QNXNTO__)
    "QNX"
    #if   defined(_NTO_VERSION)
        " " value(_NTO_VERSION)
    #elif defined(BBNDK_VERSION_CURRENT)
        " " value(BBNDK_VERSION_CURRENT)
    #endif
#elif defined(sinux)
    "Reliant UNIX"
#elif defined(_SCO_DS)
    "SCO OpenServer"
#elif defined(sun) || defined(__sun)
    #if defined(__SVR4) || defined(__svr4__)
        "Solaris"
    #else
        "SunOS"
    #endif
#elif defined(__VOS__)
    "Stratus VOS " value(__VOS__)
#elif defined(__SYLLABLE__)
    "Syllable"
#elif defined(__SYMBIAN32__)
    "Symbian OS"
#elif defined(__osf__) || defined(__osf)
    "Tru64 (OSF/1)"
#elif defined(ultrix) || defined(__ultrix) || defined(__ultrix__)
    "Ultrix"
#elif defined(_UNICOS)
    "UNICOS " value(_UNICOS)
#elif defined(_CRAY) || defined(__crayx1)
    "UNICOS/mp"
#elif defined(sco) || defined(_UNIXWARE7)
    "UnixWare"
#elif defined(_UWIN)
    "U/Win"
#elif defined(VMS) || defined(__VMS)
    "VMS " value(__VMS_PER)
#elif defined(__VXWORKS__) || defined(__vxworks)
    "VxWorks"
    #if   defined(_WRS_VXWORKS_MAJOR)
        " " value(_WRS_VXWORKS_MAJOR)
        "." value(_WRS_VXWORKS_MINOR)
        "." value(_WRS_VSWORKS_MAINT)
    #endif
    #if defined(__RTP__)
        " Real-Time"
    #endif
    #if defined(_WRS_KERNEL)
        " Kernel"
    #endif
#elif defined(_MSVC_) ||                                                \
      defined(_WIN16) || defined(_WIN32) || defined(_WIN64) ||          \
      defined(__WIN32__) || defined(__WINDOWS__) ||                     \
      defined(_WIN32_WCE)
    "Windows"
    #if   defined(_WIN32_WCE)
        " CE " value(_WIN32_WCE)
    #elif defined(_MSVC_)
        " MSVC"
    #endif
#elif defined(_WINDU_SOURCE)
    "Wind/U " value(_WINDU_SOURCE) " Environment"
#elif defined(__MVS__) || defined(__HOS_MVS__)
    "z/OS"
#else
    "*nix"
#endif
    " "
    QSTR_HOST_ARCH
    " "
#if defined(DEBUG)
    "** DEBUG ** "
#endif
    "host architecture build",

/*  Report HQA configuration information
 *
 *  FIXME: Add this section
 *
 */


/* Report emulation modes */

#if !defined(_ARCHMODE2)
    "Mode:"
#else
    "Modes:"
#endif
#if defined(_370)
    " " _ARCH_370_NAME
#endif
#if defined(_390)
    " " _ARCH_390_NAME
#endif
#if defined(_900)
    " " _ARCH_900_NAME
#endif
    ,

    "Max CPU Engines: " QSTR(MAX_CPU_ENGINES),

#if !defined(_MSVC_)
  #if defined(NO_SETUID)
    "Without setuid support",
  #else
    "Using   "
    #if defined(HAVE_SETRESUID)
     "setresuid()"
    #elif defined(HAVE_SETREUID)
     "setreuid()"
    #else
     "(UNKNOWN)"
    #endif
     " for setting privileges",
  #endif
#endif

#if defined( OPTION_FTHREADS )
    "Using   Fish threads Threading Model",
#else
    "Using   POSIX threads Threading Model",
#endif

#if        OPTION_MUTEX_DEFAULT == OPTION_MUTEX_NORMAL
    "Using   Normal Mutex Locking Model",
#elif      OPTION_MUTEX_DEFAULT == OPTION_MUTEX_ERRORCHECK
    "Using   Error-Checking Mutex Locking Model",
#elif      OPTION_MUTEX_DEFAULT == OPTION_MUTEX_RECURSIVE
    "Using   Recursive Mutex Locking Model",
#else
    "Using   (undefined) Mutex Locking Model",
#endif

#if defined(OPTION_SYNCIO)
    "With    Syncio support",
#else
    "Without Syncio support",
#endif

#if defined(OPTION_SHARED_DEVICES)
    "With    Shared Devices support",
#else
    "Without Shared Devices support",
#endif

#if defined(OPTION_DYNAMIC_LOAD)
    "With    Dynamic loading support",
#else
    "Without Dynamic loading support",
#endif

#if defined(HDL_BUILD_SHARED)
    "Using   shared libraries",
#else
    "Using   static libraries",
#endif

#if defined(EXTERNALGUI)
    "With    External GUI support",
#else
    "Without External GUI support",
#endif

// (only report when full/complete keepalive is not available)
#if !defined( HAVE_FULL_KEEPALIVE )
  #if defined( HAVE_PARTIAL_KEEPALIVE )
      "With    Partial TCP keepalive support",
  #elif defined( HAVE_BASIC_KEEPALIVE )
      "With    Basic TCP keepalive support",
  #else
      "Without TCP keepalive support",
  #endif
#endif

#if defined(ENABLE_IPV6)
    "With    IPV6 support",
#else
    "Without IPV6 support",
#endif

#if defined(OPTION_HTTP_SERVER)
    "With    HTTP Server support",
#if defined(VERBOSE_VERSION) && defined(PKGDATADIR)
    "        HTTP document default root directory is "PKGDATADIR,
#endif
#else
    "Without HTTP Server support",
#endif

#ifdef VERBOSE_VERSION
#if defined(ENABLE_CONFIG_INCLUDE)
    "With    CONFIG_INCLUDE support",
#else
    "Without CONFIG_INCLUDE support",
#endif

#if defined(ENABLE_SYSTEM_SYMBOLS)
    "With    SYSTEM_SYMBOLS support",
#else
    "Without SYSTEM_SYMBOLS support",
#endif

#if defined(ENABLE_BUILTIN_SYMBOLS)
    "With    CONFIG_SYMBOLS support",
#else
    "Without CONFIG_SYMBOLS support",
#endif
#endif

#if defined(NO_IEEE_SUPPORT)
    "Without IEEE support",
#else
    #if defined(HAVE_SQRTL)
        "With    sqrtl support",
    #else
        "Without sqrtl support",
    #endif
#endif

#if defined(NO_SIGABEND_HANDLER)
    "Without SIGABEND handler",
#else
    "With    SIGABEND handler",
#endif

#if defined(CCKD_BZIP2)
    "With    CCKD BZIP2 support",
#else
    "Without CCKD BZIP2 support",
#endif

#if defined(HET_BZIP2)
    "With    HET BZIP2 support",
#else
    "Without HET BZIP2 support",
#endif

#if defined(HAVE_LIBZ)
    "With    ZLIB support",
#else
    "Without ZLIB support",
#endif

#if defined(HAVE_REGEX_H) || defined(HAVE_PCRE)
    "With    Regular Expressions support",
#else
    "Without Regular Expressions support",
#endif

#if defined(ENABLE_OBJECT_REXX)
    "With    Object REXX support",
#else
    "Without Object REXX support",
#endif
#if defined(ENABLE_REGINA_REXX)
    "With    Regina REXX support",
#else
    "Without Regina REXX support",
#endif

#if defined(OPTION_HAO)
    "With    Automatic Operator support",
#else
    "Without Automatic Operator support",
#endif

    "Without National Language Support",

    "Machine dependent assists:"
#if !defined( ASSIST_CMPXCHG1  ) \
 && !defined( ASSIST_CMPXCHG4  ) \
 && !defined( ASSIST_CMPXCHG8  ) \
 && !defined( ASSIST_CMPXCHG16 ) \
 && !defined( ASSIST_FETCH_DW  ) \
 && !defined( ASSIST_STORE_DW  ) \
 && !defined( CAN_IAF2 )
    " (none)",
#else
  #if defined( ASSIST_CMPXCHG1 )
                    " cmpxchg1"
  #endif
  #if defined( ASSIST_CMPXCHG4 )
                    " cmpxchg4"
  #endif
  #if defined( ASSIST_CMPXCHG8 )
                    " cmpxchg8"
  #endif
  #if defined( ASSIST_CMPXCHG16 )
                    " cmpxchg16"
  #endif
  #if defined( ASSIST_FETCH_DW )
                    " fetch_dw"
  #endif
  #if defined( ASSIST_STORE_DW )
                    " store_dw"
  #endif
  #if defined( CAN_IAF2 )
                    " hatomics"
    #if CAN_IAF2 == 3
      "=C11"
    #elif CAN_IAF2 == 2
      "=gccIntrinsics"
    #endif
  #endif
    ,
#endif

};

/*-------------------------------------------------------------------*/
/* Retrieve ptr to build information strings array...                */
/*         (returns #of entries in array)                            */
/*-------------------------------------------------------------------*/
DLL_EXPORT int  get_buildinfo_strings(const char*** pppszBldInfoStr)
{
    if (!pppszBldInfoStr) return 0;
    *pppszBldInfoStr = build_info;
    return ( sizeof(build_info) / sizeof(build_info[0]) );
}

/*-------------------------------------------------------------------*/
/* Display version, copyright and build date                         */
/*-------------------------------------------------------------------*/
DLL_EXPORT void display_version( FILE* f, int httpfd, char* prog )
{
#if defined(EXTERNALGUI)
    /* If external gui being used, set stdout & stderr streams
       to unbuffered so we don't have to flush them all the time
       in order to ensure consistent sequence of log messages.
    */
    if (extgui)
    {
        setvbuf(stderr, NULL, _IONBF, 0);
        setvbuf(stdout, NULL, _IONBF, 0);
    }
#endif /*EXTERNALGUI*/

    /* Log version */

    if (f != stdout)
        if (httpfd)
            hprintf( httpfd, MSG( HHC01413, "I", prog, VERSION ));
        else
            fprintf( f, MSG( HHC01413, "I", prog, VERSION ));
    else
        WRMSG( HHC01413, "I", prog, VERSION );

    /* Log Copyright */

    if (f != stdout)
        if (httpfd)
            hprintf( httpfd, MSG( HHC01414, "I", HERCULES_COPYRIGHT ));
        else
            fprintf( f, MSG( HHC01414, "I", HERCULES_COPYRIGHT ));
    else
        WRMSG( HHC01414, "I", HERCULES_COPYRIGHT );

    /* Log build date/time */

    if (f != stdout)
        if (httpfd)
            hprintf( httpfd, MSG( HHC01415, "I", __DATE__, __TIME__ ));
        else
            fprintf( f, MSG( HHC01415, "I", __DATE__, __TIME__ ));
    else
        WRMSG( HHC01415, "I", __DATE__, __TIME__ );

} /* end function display_version */

/*-------------------------------------------------------------------*/
/* Display build options                                             */
/*-------------------------------------------------------------------*/
DLL_EXPORT void display_build_options( FILE* f, int httpfd )
{
    unsigned int i;
    const char** ppszBldInfoStr = NULL;

    if (f != stdout)
        if (httpfd)
            hprintf( httpfd, MSG( HHC01416, "I" ));
        else
            fprintf( f, MSG( HHC01416, "I" ));
    else
        WRMSG( HHC01416, "I" );

    if (!(i = get_buildinfo_strings( &ppszBldInfoStr )))
    {
        if (f != stdout)
            if (httpfd)
                hprintf( httpfd, MSG( HHC01417, "I", "(none)" ));
            else
                fprintf( f, MSG( HHC01417, "I", "(none)" ));
        else
            WRMSG( HHC01417, "I", "(none)" );
    }
    else
    {
        for(; i; i--, ppszBldInfoStr++ )
        {
            if (f != stdout)
                if (httpfd)
                    hprintf( httpfd, MSG( HHC01417, "I", *ppszBldInfoStr ));
                else
                    fprintf( f, MSG( HHC01417, "I", *ppszBldInfoStr ));
            else
                WRMSG( HHC01417, "I", *ppszBldInfoStr );
        }
    }

    if (f != stdout)
        if (httpfd)
            display_hostinfo( &hostinfo, NULL, httpfd );
        else
            display_hostinfo( &hostinfo, f, 0 );
    else
        display_hostinfo( &hostinfo, f, 0 );

} /* end function display_build_options */
