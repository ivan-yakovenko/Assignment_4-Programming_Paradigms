# DLL creation

--- 

# Compilation/Linking/Checking

---

## Compiling

```g++ -c Assignment_4/CaesarCipher/mylib.cpp -o mylib.o```

## Linking

```g++ -shared -o mylib.so mylib.o```

## Checking

```nm mylib.so```

``` 
                 U __DefaultRuneLocale
0000000000003f34 T __Z7isasciii
0000000000003e4c T __Z7isloweri
0000000000003e24 T __Z7isupperi
0000000000003ea8 T __Z8__istypeim
                 U ___maskrune
0000000000003e74 T _decrypt
0000000000003cd4 T _encrypt
                 U _strlen
```

