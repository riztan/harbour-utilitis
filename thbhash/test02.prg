//-----------------------------------------------------------------------------
// Ejemplo uso de THbHash
// 
// Author: Manuel Expósito
//-----------------------------------------------------------------------------

procedure main 

    local hash := { "key1" => "valor1", "key2" => "valor2", "key3" => "valor3"}
    local h := THbHash():new()

    SetMode( 25, 80 )

    ? "Numero de elementos:", h:len(), len( hash )
 
    h:setHash( hash )

    ? "Numero de elementos:", h:len(), len( hash )

    h:autor := "Manu Exposito"
    ? h:autor, h:get( "autor" )
 
    hash[ "prueba" ] = "prueba desde fuera"
    
    ? "------------------------------------------------------"
    ? "Keys:" 
    ? hb_valtoexp( h:keys() ) 
    ? "Values:" 
    ? hb_valtoexp( h:values() ) 
    ? "Todo:"
    ? hb_valtoexp( hash )

    h:kiko := "lolo"
    ? "------------------------->", h:kiko
    ? h:kika

    h:end()

    ? "------------------------------------------------------"
    ? "Despues del end el hash sige vivo:"
    ? hb_valtoexp( hash )

    alert( "Fin" )

return
