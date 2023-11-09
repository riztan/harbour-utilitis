//-----------------------------------------------------------------------------
// Ejemplo usu de THbHash
//
// Author: Manuel Expósito
//-----------------------------------------------------------------------------

procedure main 

    local h := THbHash():new()
    local i, c, cKey, aKeys

//    SetMode( 25, 80 )
    
    CLS

    raya()

    ? "valtype( h ) => ", valtype( h ) , " | "
    ?? "valtype( h:getHash() ) => ", valtype( h:getHash() ) 

    raya()

    ? "List of Methods:"
    ? hb_valtoexp( __objGetMethodList( h ) )

    for i := 1 to 10
        c := hb_ntos( i )
        h:set( "key" + c, "value" + c )
    next

    h:cAuthor := "Manu Exposito"
    ? "Author: ", h:cAuthor, "Key con mayusculas y minusculas:", h:cAuThOr
    h:cAuthor := "Yo Exposito"
    
    raya()

    h:hash[ "colaborador" ] := "Riztan"
    ah := h:hash // ah := h:getHash()
    ? h:hash[ "colaborador" ], h:colaborador, h:get( "colaborador" ), ah[ "colaborador" ]
    
    para()

    h:key1 := { 1, 2, 3, 4 }
    h:add( "key11", { || alert( "Fin!" ) } )

    raya()

    ? "Delete key10.           =>  h:del( 'key10' )    => ", h:del( "key10" )
    ? "Scan the key5           =>  h:scan( 'key5' )    => ", hb_ntos( h:scan( "key5" ) ), "( Return position key5 ) "
    ? "Value in position 6     =>  h:valueAt( 6 )      => ", hb_valtoexp( h:valueAt( 6 ) )
    ? "Is defined 'key8'?      =>  h:hasKey( 'key8' )  => ", h:hasKey( "key8" )
    ? "Is not defined 'key10'? =>  h:hasKey( 'key10' ) => ", h:hasKey( "key10" )

    raya()

    ? "Number of elements:", hb_ntos( h:len() )

    ? "Keys:" 
    ? hb_valtoexp( h:keys() ) 
    ? "Values:" 
    ? hb_valtoexp( h:values() ) 

    para()
    raya()

    aKeys := h:Keys()

    FOR EACH cKey IN aKeys
       ? cKey, "=>" , hb_valtoexp( h:get( cKey ) )
       if hb_isBlock( h:get( cKey ) ) ; eval( h:get( cKey ) ) ; endif
    NEXT

    h:end()

return

//-----------------------------------------------------------------------------

static procedure raya( n )

    if valtype( n ) != 'N'
        n := MaxCol()
    endif

    ? Replicate( "-", n )

return

//-----------------------------------------------------------------------------

static procedure para( n )

    if valtype( n ) != 'N'
        n := 60
    endif
    ?
    raya()
    ? "Presiona una tecla o espera " + hb_ntoc( n ) + " segundos..."
    inkey( n )

return

//-----------------------------------------------------------------------------
