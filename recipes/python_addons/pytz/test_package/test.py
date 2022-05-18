from pytz import timezone
import pytz

utc = pytz.utc
assert utc.zone == 'UTC'

eastern = timezone('US/Eastern')
assert eastern.zone == 'US/Eastern'
