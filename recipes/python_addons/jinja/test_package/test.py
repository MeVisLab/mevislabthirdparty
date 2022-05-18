import jinja2
from jinja2 import Environment, BaseLoader

tmpl = Environment(loader=BaseLoader()).from_string("Hello {{ name }}!")
print(tmpl.render(name="World"))
