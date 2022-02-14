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

/*$(document).ready(function(){   
  $('.project').click(function() {
    $('.project').css('height', '100vh');
    $('.project').css('background-color', 'white');
    $('.project').css('color', 'black');
    $('.project').css('justify-content', 'left');
  });
});*/

let disableScroll = false;

function expand(id) {
  //Set default open/close settings
      $('.logo').css('color', 'black !important');
      $('#'+id).toggleClass('active');
      $('#'+id+'.p').toggleClass('display');
      $('html, body').animate({
        scrollTop: $('#'+id).offset().top-70
      }, 500);
      TopScroll = $('#'+id).offset().top-70;
      LeftScroll = window.pageXOffset;

      // if scroll happens, set it to the previous value
      if (disableScroll === false) {
        window.onscroll = function() {
          window.scrollTo(LeftScroll, TopScroll);
        };
        disableScroll = true;
      } else {
        window.onscroll = function() {};
        disableScroll = false;
      }
}

$(function() {
  var rotation = 0, 
      scrollLoc = $(document).scrollTop();
  $(window).scroll(function() {
      var newLoc = $(document).scrollTop();
      var diff = scrollLoc - newLoc;
      rotation += diff, scrollLoc = newLoc;
      var rotationStr = "rotate(" + rotation + "deg)";
      $(".gear").css({
          "-webkit-transform": rotationStr,
          "-moz-transform": rotationStr,
          "transform": rotationStr
      });
  });
})