//-----------------------------------------------------------------------------
// Ejemplo 2
// Autor: Manu Expósito
//-----------------------------------------------------------------------------

procedure main

    local ain := { "prueba", 2, .f., date(), time() }
    local a := THbArray():new( ain )
    local i, nLen

    cls
 
    para( 100, "Empezamos!!!!, presiona <INTRO> para continuar..." )
    ? a:className(), len( a ), a:getSize()
    para( "Seguimos?", 100 )

    ? "Total elementos:", nLen := a:getSize()

    raya() 
    ? "Visualizacion de elemtos:" 
    ?
    for i := 1 to nLen
        ? i, a:value( i )
    next

    raya() 

    if a:goTo( 3 ):delete()
        ? "Se ha borrado el elemento 3"
    else
        ? "No se ha podido borrar"
    end if

    raya() 

    ? "Numero de lementos ahora:", nLen := a:getSize()

    raya() 
    ? "Visualizacion de elemtos:"

    for i := 1 to nLen
        ? i, a:value( i )
    next

    para( 100 )

    a:end()

return

//-----------------------------------------------------------------------------
#include "utiles.prg"
//-----------------------------------------------------------------------------
