import tomli

toml_str = """
[[players]]
name = "Lehtinen"
number = 26

[[players]]
name = "Numminen"
number = 27
"""

toml_dict = tomli.loads(toml_str)
assert toml_dict == {
    "players": [{"name": "Lehtinen", "number": 26}, {"name": "Numminen", "number": 27}]
}
