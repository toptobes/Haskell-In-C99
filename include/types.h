#ifndef FUNCTIONALC_TYPES_H
#define FUNCTIONALC_TYPES_H

#define NoneConstraint None
typedef struct {} None;

#define GET_7TH_ARG(_1, _2, _3, _4, _5, _6, _7, ...) _7
#define EXPAND(...) , ##__VA_ARGS__

#define NARGS(...) NARGS_IMPL(__VA_ARGS__, 6, 5, 4, 3, 2, 1, 0)
#define NARGS_IMPL(_1, _2, _3, _4, _5, _6, N, ...) N

#define SS1(a)                a a;
#define SS2(a, b)             a a; SS1(b)
#define SS3(a, b, c)          a a; SS2(b, c)
#define SS4(a, b, c, d)       a a; SS3(b, c, d)
#define SS5(a, b, c, d, e)    a a; SS4(b, c, d, e)
#define SS6(a, b, c, d, e, f) a a; SS5(b, c, d, e, f)
#define SEMICOLON_SEPARATED(...) GET_7TH_ARG(__VA_ARGS__, SS6, SS5, SS4, SS3, SS2, SS1)(__VA_ARGS__)

#ifdef DOUBLEPP
    #define CAST_FN(name, T, body, c)                    \
        _$$ifndef name##2##T##CF                      \
            _$$define name##2##T##CF                  \
            T name##2##T (name name) { return body; } \
        _$$endif
#else
    #define CAST_FN(name, T, body, c) T name##2##T##c (name name) { return body; }
#endif

#define CF1(name, cnt)
#define CF2(name, a, cnt)             CAST_FN(name, a, name.as.a, cnt)                         CF1(name, cnt)
#define CF3(name, a, b, cnt)          CAST_FN(name, b, name.as.a._base, cnt)                   CF2(name, a, cnt)
#define CF4(name, a, b, c, cnt)       CAST_FN(name, c, name.as.a._base._base, cnt)             CF3(name, a, b, cnt)
#define CF5(name, a, b, c, d, cnt)    CAST_FN(name, d, name.as.a._base._base._base, cnt)       CF4(name, a, b, c, cnt)
#define CF6(name, a, b, c, d, e, cnt) CAST_FN(name, e, name.as.a._base._base._base._base, cnt) CF5(name, a, b, c, d, cnt)
#define CAST_FNS(...) GET_7TH_ARG(__VA_ARGS__, CF6, CF5, CF4, CF3, CF2, CF1)(__VA_ARGS__, __COUNTER__)

#define CFG1(name)
#define CFG2(name, a)             CAST_FNS(name, a##Constraint)
#define CFG3(name, a, b)          CAST_FNS(name, a##Constraint) CFG2(name, b)
#define CFG4(name, a, b, c)       CAST_FNS(name, a##Constraint) CFG3(name, b, c)
#define CFG5(name, a, b, c, d)    CAST_FNS(name, a##Constraint) CFG4(name, b, c, d)
#define CFG6(name, a, b, c, d, e) CAST_FNS(name, a##Constraint) CFG5(name, b, c, d, e)
#define CAST_FN_GROUPS(...) GET_7TH_ARG(__VA_ARGS__, CFG6, CFG5, CFG4, CFG3, CFG2, CFG1)(__VA_ARGS__)

#ifdef DOUBLEPP
    #define TypeClassConstraintsIfPP(name, parent) _$$define name##Constraint name parent##Constraint
#else
    #define TypeClassConstraintsIfPP(...)
#endif

#define CreateTypeClassImpl(name, parent) typedef union { parent _base; struct {} _derived; } name; TypeClassConstraintsIfPP(name, parent)
#define CreateTypeClass(name, ...) CreateTypeClassImpl(name EXPAND(__VA_ARGS__))

#define CreateDataImpl(name, init, ...) typedef struct { union { SEMICOLON_SEPARATED(__VA_ARGS__) } as; init; } name; CAST_FN_GROUPS(name, __VA_ARGS__)
#define CreateData(name, init, ...) CreateDataImpl(name, init EXPAND(__VA_ARGS__))

#define unconstrained , None
#define constrainedBy ,
#define containing ,

#endif//FUNCTIONALC_TYPES_H
