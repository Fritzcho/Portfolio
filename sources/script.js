$(document).ready(function(){
        setTimeout(function () {
          $("#hero-h1").css('border-right', 'none');
        }, 4000);
    });

$(document).ready(function(){
        $("#hero-h2").css('opacity', '0');
        setTimeout(function () {
            $("#hero-h2").css('opacity', '1');
        }, 4100);
    });

$(document).ready(function(){       
  var scroll_pos = 0;
  $(document).scroll(function() { 
    scroll_pos = $(this).scrollTop();
      if(scroll_pos > $(".project-items").offset().top) {
        $(".logo").css('color', 'white');
      } else {
        $(".logo").css('color', 'black');
      }
  });
});

