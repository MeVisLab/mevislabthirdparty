from datetime import datetime
from typing import Optional
from pydantic import BaseModel


class User(BaseModel):
    id: int
    name: str = "John Doe"
    signup_ts: Optional[datetime] = None
    friends: list[int] = []


external_data = {"id": "123", "signup_ts": "2017-06-01 12:22", "friends": [1, "2", b"3"]}
user = User(**external_data)
assert user.name == "John Doe"
assert user.id == 123
assert user.friends == [1, 2, 3]
