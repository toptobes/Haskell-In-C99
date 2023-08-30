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

#define ApplicativeConstraint Applicative constrained by FunctorConstraint
CreateTypeClass(Applicative constrained by Functor)

#define MonadConstraint Monad constrained by ApplicativeConstraint
CreateTypeClass(Monad constrained by Applicative)

#define TestConstraint Test unconstrained
CreateTypeClass(Test unconstrained)

CreateData(Maybe containing void* value; int isNothing constrained by Monad, Test)

Maybe Just(int *p) {
    return (Maybe) { .isNothing = 0, .value = p };
}

void* fromJust(Maybe m) {
    return m.value;
}

typedef void* FmapFn(void*, void*);

Maybe fmapMaybe(FmapFn **fn, Maybe m) {
    return m.isNothing ? m : Just (Call (fn, fromJust (m)));
}

int* add3(void *, const int *a) {
    return Allocated(*a + 3)
}

int main(int argc)
{
    return deref(int) fromJust $ fmapMaybe $ Λ (add3), Just (&argc) end2
}

//#define fmap(name, args, ...) fmapImpl(name, args, EXPAND(__VA_ARGS__))
//#define fmapImpl(...)

//fmap ((Λ (add3), myMaybe), FmapFn** to Maybe to Maybe)
//return *(Call(Λ (add3), &argc));
