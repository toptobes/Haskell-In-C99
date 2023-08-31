#ifndef FUNCTIONALC_MISC_H
#define FUNCTIONALC_MISC_H

#define to ,

#define Allocated(t) ({              \
    typeof(t) *q = malloc(sizeof q); \
    *q = t;                          \
    q;                               \
});

#ifdef DOUBLEPP
    #define DEFERRED_ALLOCATED #define Allocated(t) ({  typeof(t) *q = malloc(sizeof q); *q = t; q; })
    DEFERRED_ALLOCATED
#endif

#define $ (

#define end  ;
#define end1 );
#define end2 ));
#define end3 )));
#define end4 ))));
#define end5 )))));

#define deref(T) *(T*)

#endif //FUNCTIONALC_MISC_H
