## Why am I doing this in C, you ask?

### because I have nothing better to do with my life

```c
/* using the double preprocessing version */

CreateTypeClass(Functor unconstrained)
CreateTypeClass(Applicative constrainedBy Functor)
CreateTypeClass(Monad constrainedBy Applicative)

CreateData(Maybe containing void* value; int isNothing constrainedBy Monad)

Maybe Just(int *p) 
{
    return (Maybe) { .isNothing = 0, .value = p };
}

void* fromJust(Maybe m) 
{
    return m.value;
}

Maybe fmapMaybe(Maybe m, void* (**fn)(void*, void*)) 
{
    return m.isNothing ? m : Just $ Call $ fn, fromJust (m) end2
}

// _Generic's not really extensible ik, might break my rules slightly and add a pre-compilation script to collect
// typeclass method implementations and aggregate them in the _Generics
#define fmap(self, ...) _Generic(self, Maybe: fmapMaybe(self, ##__VA_ARGS__))

// Using a deferred definition here so fmap can be used with $ as well
// Again could add automation script to ./run for this though that's kinda cheating
#define DEFERRED_FMAP #define fmap(self, ...) _Generic(self, Maybe: fmapMaybe(self, ##__VA_ARGS__))
DEFERRED_FMAP

int* add(const int amount, const int *a) 
{
    return Allocated $ *a + amount end1
}

int main(int argc)
{
    return deref(int) fromJust $ fmap $ Just (&argc), λ (add, 3) end2
}
```

There's two slightly different (non-source-compatible) versions of the interface:

1. Use `./run` which defines `DOUBLEPP` and runs the C preprocessor twice,
   enabling additional "smoothing out" of the API.
2. Run it normally w/ cmake or whatever, which also works, but provides a
   slightly rougher/more manual interface.

The preprocessor auto-generates functions to cast to base types in a safe manner.
If you're using mode #1, the functions will look like `Maybe2Monad` or
`Maybe2Functor`, whereas if you use mode #2, they'll look like `Maybe2MonadN`
where `N` is some number (to prevent name clashing in the event of multiple
type constraints).

I'll finish this README later, I swear

TODO: more typesafety and stuff

*please, gods of C, don't come after me for this abomination*
