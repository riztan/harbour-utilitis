//-----------------------------------------------------------------------------
// Ejemplo 1
// Autor: Manu Expósito
//-----------------------------------------------------------------------------

procedure main

    local ain := { "prueba", 2, .f., date(), time() }
    local a := THbArray():new( ain )
    local i, nLen

    cls

    para(, "Empezamos!!!!..." )

    ? a:className(), len( ain )

    ? nLen := a:getSize()

    raya()

    for i := 1 to nLen
        ? i, a:value( i )
    next

    raya()

    a:goTo( 3 ):set( "Elemento 3 modificado")
    // o tambien
    a:goTo( 4 ):update( "Elemento 4 modificado")

    for i := 1 to nLen
        ? i, a:value( i )
    next

    para(, "Se termino!!!")

    a:free()

return

//-----------------------------------------------------------------------------
#include "utiles.prg"
//-----------------------------------------------------------------------------
