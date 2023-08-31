#pragma clang diagnostic push

#include <stdio.h>
#include <malloc.h>
#include "../include/closures.h"
#include "../include/types.h"
#include "../include/misc.h"

//#define BIND_FN(name, R, ...) R (*name)(__VA_ARGS__)
//
//#define $(x, fn, y) fn(x, y)
//
//#define TOKEN_PASTE(x, y) T0KEN_PASTE(x, y)
//#define T0KEN_PASTE(x, y) x ## y
//
//#define Functor(A) A*
//#define Applicative(A) A*
//#define Monad(A) A*
//#define Maybe(A) A*
//
//typedef void* (*GenericFn)();
//
//typedef struct {
//    void* value;
//} FunctorT;
//
//#define fmap(f, fn) _Generic()
//
//typedef struct {
//    FunctorT _;
//} ApplicativeT;
//
//Applicative(void) _pure(void*);
//Applicative(void) _apply(Applicative(GenericFn), Applicative(void));
//
//typedef struct {
//    ApplicativeT _;
//} MonadT;
//
//Monad(void) _bind(Monad(void), Monad(void) (*)(void *));
//
//#define Just(X) ((Maybe(typeof(X))) &((MaybeT) { ._ = (void*) (X), .isNothing = 0 }))
//#define Nothing ((void*) ((MaybeT) { ._ = NULL, .isNothing = 1 }))
//
//#define maybe_fmap(maybe, fn)       \
//    ((MaybeT*) maybe)->isNothing    \
//        ? Nothing                   \
//        : Just(Call(fn, *maybe))  \
//
//typedef struct {
//    int num;
//} TestT;
//
//typedef TestT Int2Test(void*, int);
//
//TestT wrap(void* _, int num) {
//    return (TestT) { num };
//}

typedef int FilterFn(void*, int);

void print_filtered(int n, FilterFn **filter) {
    int i;
    for (i = 1; i <= n; ++i)
        if (Call(filter, i))
            printf("%d ", i);
    puts("");
}

const int divisor = 3;

int divisibleBy(int d, int n) {
    return (n % d) == 0;
}

void test() {
    print_filtered (100, λ (divisibleBy, divisor));
}

#define FunctorConstraint Functor unconstrained
CreateTypeClass(Functor unconstrained)

#define ApplicativeConstraint Applicative constrainedBy FunctorConstraint
CreateTypeClass(Applicative constrainedBy Functor)

#define MonadConstraint Monad constrainedBy ApplicativeConstraint
CreateTypeClass(Monad constrainedBy Applicative)

#define TestConstraint Test unconstrained
CreateTypeClass(Test unconstrained)

CreateData(Maybe containing void* value; int isNothing constrainedBy Monad, Test)

const Maybe Nothing = (Maybe) { .isNothing = 1 };

Maybe Just(int *p) {
    return (Maybe) { .isNothing = 0, .value = p };
}

void* fromJust(Maybe m) {
    return m.value;
}

typedef void* FmapFn(void*, void*);

Maybe fmapMaybe(Maybe m, FmapFn **fn) {
    #ifdef DOUBLEPP
        return m.isNothing ? m : Just $ Call $ fn, fromJust (m) end2
    #else
        return m.isNothing ? m : Just $ Call (fn, fromJust (m)) end1
    #endif
}

int* add(const int amount, const int *a) {
    #ifdef DOUBLEPP
        return Allocated $ *a + amount end1
    #else
        return Allocated (*a + amount)
    #endif
}

#define fmap(self, ...) _Generic(self, Maybe: fmapMaybe(self, ##__VA_ARGS__))
#ifdef DOUBLEPP
    #define DEFERRED_FMAP #define fmap(self, ...) _Generic(self, Maybe: fmapMaybe(self, ##__VA_ARGS__))
    DEFERRED_FMAP
#endif

int main(int argc)
{
    #ifdef DOUBLEPP
        return deref(int) fromJust $ fmap $ Just (&argc), λ (add, 3) end2
    #else
        return deref(int) fromJust $ fmapMaybe $ Just (&argc), λ (add, 3) end2
    #endif
}
