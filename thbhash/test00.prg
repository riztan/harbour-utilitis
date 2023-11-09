//-----------------------------------------------------------------------------
// Ejemplo uso de THbHash
//
// Author: Manuel Expósito
//-----------------------------------------------------------------------------

procedure main 

    local h := THbHash():new()
    local i, c, n

    SetMode( 25, 80 )

    ? "Tipo de la variable h", valtype( h ), "y h:getHash()", valtype( h:getHash() )

    for i := 1 to 10
        c := hb_ntos( i )
        h:set( "key" + c, "value" + c )
    next

    ? "Numero de elementos:", n:= h:len()
    ? "------------------------------------------------------"

    for i := 1 to n
        ? "Clave:", c := "key" + hb_ntos( i ), "Valor:", h:get( c )
    next

    ? h:key1, h:get( "key1" )

    h:autor := "Manu Exposito"
    ? h:autor, h:get( "autor" )

    h:hash[ "colaborador" ] := "Riztan"
    ? h:hash[ "colaborador" ], h:colaborador, h:get( "colaborador" )
    
    ? "------------------------------------------------------"
    ? "Keys:" 
    ? hb_valtoexp( h:keys() ) 
    ? "Values:" 
    ? hb_valtoexp( h:values() ) 

    h:end()

    alert( "Fin" )

return
