from markupsafe import Markup, escape

assert escape('<script>alert(document.cookie);</script>') == '&lt;script&gt;alert(document.cookie);&lt;/script&gt;'

assert Markup("Hello <em>%s</em>") % '"World"' == 'Hello <em>&#34;World&#34;</em>'
