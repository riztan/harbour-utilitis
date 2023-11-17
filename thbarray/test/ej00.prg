//-----------------------------------------------------------------------------
// Ejemplo 0
// Autor: Manu Expósito
//-----------------------------------------------------------------------------

procedure main

    local ain := { "prueba", 2, .f., date(), time() }
    local a := THbArray():new( ain )
    local i, nLen

    cls
  
    para(, "Empezamos!!!!..." )
    ? a:className(), len( ain ), a:len()
    para( 100, "Seguimos?" )

    a:add( "Elemento 1" )
    a:add( "Elemento 2" )
    a:add( "Elemento 3" )
    a:add( "Elemento 4" )                        
    a:add( "Elemento 5" ) 

    ? nLen := a:len()
    raya()

    for i := 1 to nLen
        ? i, a:value( i )
    next

    para()

    a:goTop()

    i := 0
    while !a:eof()
        ? ++i, a:current()
        a:skip()
    end

    para()

    a:goBottom()

    i := 0
    while !a:bof()
        ? ++i, a:current()
        a:skip( -1 )
    end

    para(, "Se termino" )

    a:end()

return

//-----------------------------------------------------------------------------
#include "utiles.prg"
//-----------------------------------------------------------------------------
