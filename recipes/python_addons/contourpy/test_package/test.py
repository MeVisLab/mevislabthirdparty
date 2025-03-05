from contourpy import contour_generator

z = [[0.0, 0.1], [0.2, 0.3]]
cont_gen = contour_generator(z=z)
print(cont_gen.filled(0.15, 0.25))
