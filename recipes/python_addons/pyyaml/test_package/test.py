import yaml

y = """
Director:
  name: Spielberg
  Movies:
    - Movie:
        title: E.T.
        year: 1975
    - Movie:
        title: Jaws
        year: 1982
"""

yaml.load(y, Loader=yaml.SafeLoader)
yaml.load_all(y, Loader=yaml.SafeLoader)
yaml.safe_load(y)

print(yaml.dump(yaml.safe_load(y)))