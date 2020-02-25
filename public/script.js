$( document ).ready(function() {

  $(".choice").click(function() {

    $.get( "put_food_into_basket", { choice: $(this).text() } ).done(function( data ) {

      $( ".result" ).html( data );

    });

  })

});
