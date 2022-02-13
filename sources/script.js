$(function() {
    $('.bounce').click (function() {
      $('html, body').animate({scrollTop: $('div.arrow-down').offset().top}, 'slow');
      return false;
    });
  });

$(function() {
   $('.contact').click (function() {
     $('html, body').animate({scrollTop: $('footer').offset().top }, 'slow');
     return false;
   });
});

function imageClick(url) {
  window.location = url;
}

function imageClick2() {
  window.location = 'https://framer.com/share/V-sterbottensost--wwQTWvLZ9kXPyGUSpUVm/SInXVBpHx?fullscreen=1#SInXVBpHx';
}

function imageClick3() {
  window.location = 'https://framer.com/share/V-sterbottensost-mobile--zSDZSHWAg7iHe8qdYE0v/jj0ZcX4lR';
}

/*        $(document).ready( function() {
            $("#header").load("header.html");
          });*/
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
          if(scroll_pos > 600) {
              $(".logo").css('color', 'white');
          } else {
              $(".logo").css('color', 'black');
          }
      });
  });