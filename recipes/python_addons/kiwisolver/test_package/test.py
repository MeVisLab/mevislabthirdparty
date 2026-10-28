import kiwisolver

x = kiwisolver.Variable("x")
solver = kiwisolver.Solver()
solver.addConstraint(x == 42)
solver.updateVariables()
assert x.value() == 42
