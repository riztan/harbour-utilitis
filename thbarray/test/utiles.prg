//-----------------------------------------------------------------------------
// Varias funciones de apoyo
// Autor: Manu Expósito
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

static procedure raya( n, cRepe )

    if valtype( n ) != 'N'
        n := MaxCol()
    endif

    if valtype( cRepe ) != 'C'
        cRepe := "-"
    endif

    ? Replicate( "-", n )

return

//-----------------------------------------------------------------------------

static procedure para( n, cMsg, cRepe )

    if valtype( n ) != 'N'
        n := 60
    endif
    ?
    raya(, cRepe )
    if valtype( cMsg ) == 'C'
        ? cMsg
    else
        ? "Presiona una tecla o espera " + hb_ntoc( n ) + " segundos..."
    endif
    inkey( n )

return

//-----------------------------------------------------------------------------
