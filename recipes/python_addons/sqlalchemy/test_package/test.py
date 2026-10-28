import sqlalchemy

engine = sqlalchemy.create_engine("sqlite://")
with engine.connect() as connection:
    result = connection.execute(sqlalchemy.text("SELECT 42")).scalar()
assert result == 42
