#ifndef FUNCTIONALC_CLOSURES_H
#define FUNCTIONALC_CLOSURES_H

#define Λ(fn) ({            \
    typeof(&fn) temp = &fn; \
    &temp;                  \
})

#define λ(fn, ctx) ({                             \
    struct $$closure {                            \
        typeof(fn) *func;                         \
        typeof(ctx) context;                      \
    };                                            \
                                                  \
    (void*) &(struct $$closure) { fn, ctx }.func; \
})

#define EXTRACT_CLOSURE_CTX(f) (*((void**)((char*)f + sizeof(void (*)(void)))))
#define Call(f, ...) ((**(f))(EXTRACT_CLOSURE_CTX(f), __VA_ARGS__))

#endif//FUNCTIONALC_CLOSURES_H
