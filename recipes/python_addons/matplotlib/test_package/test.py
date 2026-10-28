import io

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as pyplot

figure, axes = pyplot.subplots()
axes.plot([0, 1, 2, 3], [0, 1, 4, 9])
axes.set_title("matplotlib test")

buffer = io.BytesIO()
figure.savefig(buffer, format="png")
pyplot.close(figure)

data = buffer.getvalue()
assert data[:8] == b"\x89PNG\r\n\x1a\n"
assert len(data) > 1000
