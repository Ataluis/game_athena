To compile, try :

  $  make
  $  ./spacebattle

If this does not work, you have to open spacebattle.cbp with
Code::Blocks and compile it there. For this you may need to add 
some libraries to link:
  --Settings
    --Compiler...
      --Linker settings	
        Link libraries:
        sfml-graphics
        sfml-system
        sfml-window

This game was written and designed by Fabian Farina. Most of the bitmaps were 
created with GIMP, the background was a lincense free foto found on the internet.
