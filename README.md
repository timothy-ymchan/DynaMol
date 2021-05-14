# DynaMol
Homebrew molecular dynamics code

## Dependencies
- g++ 10.2 or above
- make

## Compile

    make all -PROB <PROB_NAME>

## Simulate 
After compilation, an executable called `DynaMol` will be made (yes the name is lame). To run the code, do:

    ./DynaMol ./dminput/melting.input
