## Why am I doing this in C, you ask?

### because I have nothing better to do with my life

```c
// using double preprocessing
CreateTypeClass(Functor unconstrained)
CreateTypeClass(Applicative constrained by Functor)
CreateTypeClass(Monad constrained by Applicative)

CreateData(Maybe containing void* value; int isNothing constrained by Monad)

int* add3(void *, const int *a) 
{
    return Allocated(*a + 3)
}

int main(int argc)
{
    return deref(int) fromJust $ fmapMaybe $ Λ (add3), Just (&argc) end2
}
```

There's two slightly different (non-source-compatible) versions of the interface:

1. Use `./run` which defines `DOUBLEPP` and runs the C preprocessor twice,
   enabling additional "smoothing out" of the API.
2. Run it normally w/ cmake or whatever, which also works, but provides a
   slightly rougher/more manual interface.

I'll finish this README later, I swear

TODO: more typesafety and stuff

*please, gods of C, don't come after me for this abomination*
