/*    util.h
 *
 *    Copyright (C) 1991, 1992, 1993, 1999, 2001, 2002, 2003, 2004, 2005,
 *    2007, by Larry Wall and others
 *
 *    You may distribute under the terms of either the GNU General Public
 *    License or the Artistic License, as specified in the README file.
 *
 */

#ifdef VMS
#  define PERL_FILE_IS_ABSOLUTE(f) \
	(*(f) == '/'							\
	 || (strchr(f,':')						\
	     || ((*(f) == '[' || *(f) == '<')				\
		 && (isWORDCHAR((f)[1]) || strchr("$-_]>",(f)[1])))))

#else		/* !VMS */
#  if defined(WIN32) || defined(__CYGWIN__)
#    define PERL_FILE_IS_ABSOLUTE(f) \
	(*(f) == '/' || *(f) == '\\'		/* UNC/rooted path */	\
	 || ((f)[0] && (f)[1] == ':'))		/* drive name */
#  else		/* !WIN32 */
#  ifdef NETWARE
#    define PERL_FILE_IS_ABSOLUTE(f) \
	(((f)[0] && (f)[1] == ':')		/* drive name */	\
	 || ((f)[0] == '\\' && (f)[1] == '\\')	/* UNC path */	\
	 ||	((f)[3] == ':'))				/* volume name, currently only sys */
#  else		/* !NETWARE */
#    if defined(DOSISH) || defined(__SYMBIAN32__)
#      define PERL_FILE_IS_ABSOLUTE(f) \
	(*(f) == '/'							\
	 || ((f)[0] && (f)[1] == ':'))		/* drive name */
#    else	/* NEITHER DOSISH NOR SYMBIANISH */
#      define PERL_FILE_IS_ABSOLUTE(f)	(*(f) == '/')
#    endif	/* DOSISH */
#   endif	/* NETWARE */
#  endif	/* WIN32 */
#endif		/* VMS */

/*
=for apidoc ibcmp

This is a synonym for (! foldEQ())

=for apidoc ibcmp_locale

This is a synonym for (! foldEQ_locale())

=cut
*/
#define ibcmp(s1, s2, len)         cBOOL(! foldEQ(s1, s2, len))
#define ibcmp_locale(s1, s2, len)  cBOOL(! foldEQ_locale(s1, s2, len))

#ifdef U64TYPE
/* use a faster implementation */
#define FREEBSD_DRAND48_QUAD
#endif

#ifdef FREEBSD_DRAND48_QUAD

/* U64 is only defined under PERL_CORE, but this needs to be visible
 * elsewhere so the definition of PerlInterpreter is complete.
 */
typedef U64TYPE freebsd_drand48_t;

#else

/* see copyright in util.c */
struct FREEBSD_DRAND48_T {
    U16 seed[3];
};

typedef struct FREEBSD_DRAND48_T freebsd_drand48_t;

#endif

#define PL_RANDOM_STATE_TYPE freebsd_drand48_t
#define SEED_RAND(x) freebsd_drand48_init((U32)x)
#define RAND01() freebsd_drand48_generate_double()

/*
 * Local variables:
 * c-indentation-style: bsd
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 *
 * ex: set ts=8 sts=4 sw=4 et:
 */
