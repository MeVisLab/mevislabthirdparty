from dateutil.relativedelta import relativedelta
from dateutil.easter import easter
from dateutil.rrule import YEARLY, FR, rrule
from dateutil.parser import parse

now = parse("Sat Oct 7 17:13:46 UTC 2021")
today = now.date()

assert today.day == 7
assert today.month == 10
assert today.year == 2021

assert easter(2022).day == 17
assert easter(2022).month == 4
assert easter(2022).year == 2022

rdelta = relativedelta(easter(2021), easter(1901))

assert rdelta.days == 28
assert rdelta.months == 11
assert rdelta.years == 119
