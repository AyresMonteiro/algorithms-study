import matplotlib.pyplot as plt
import numpy as np

def convolution(a, b):
    convoluted = []
    reversed_b = b[::-1]

    a_size = len(a)
    b_size = len(b)

    for i in range(a_size + b_size - 2):
        i += 1
        total_sum = 0

        for j in range(i):
            ia = j
            ib = b_size - i + j

            if (ia < a_size and ib >= 0 and ib < b_size):
                total_sum += a[ia] * reversed_b[ib]
        
        convoluted.append(total_sum)
    
    return convoluted

# print(convolution(
#     [1, 2, 3, 4, 5, 6],
#     [1, 2, 3, 4, 5, 6]
# ))

def random_array(size):
    return np.random.randint(0, 10, size)

def get_function_by_coefficients(coefficients):
    def f(x):
        total_sum = 0

        reversed_range = range(len(coefficients))[::-1]

        for i in range(len(coefficients)):
            total_sum += coefficients[i] * (x ** reversed_range[i])
        
        return total_sum
    
    return f

def get_function_string_by_coefficients(coefficients):
    function_string = ''

    for i in range(len(coefficients)):
        coefficient = coefficients[i]
        power = len(coefficients) - i - 1

        if (coefficient != 0):
            if (coefficient > 0 and i > 0):
                function_string += ' + '
            elif (coefficient < 0):
                function_string += ' - '

            if (coefficient > 0):
                function_string += str(coefficient)
            elif (coefficient < 0):
                function_string += str(-coefficient)

            if (power > 0):
                function_string += 'x'

            if (power > 1):
                function_string += '^' + str(power)
    
    return function_string

def plot_convolution(a, b):
    convoluted = convolution(a, b)

    print(a)
    print(b)
    print(convoluted)

    left_limit = -3
    right_limit = 3
    number_of_points = 100

    ax_points = np.linspace(left_limit, right_limit, number_of_points)
    bx_points = np.linspace(left_limit, right_limit, number_of_points)
    convolutedx_points = np.linspace(left_limit, right_limit, number_of_points)

    a_function = get_function_by_coefficients(a)
    b_function = get_function_by_coefficients(b)
    convoluted_function = get_function_by_coefficients(convoluted)

    ay_points = a_function(ax_points)
    by_points = b_function(bx_points)
    convolutedy_points = convoluted_function(convolutedx_points)

    plt.plot(ax_points, ay_points, label=get_function_string_by_coefficients(a))
    plt.plot(bx_points, by_points, label=get_function_string_by_coefficients(b))
    plt.plot(convolutedx_points, convolutedy_points, label=get_function_string_by_coefficients(convoluted))

    fig = plt.gcf()
    fig.canvas.manager.set_window_title('convolution')

    plt.legend()
    plt.show()

plot_convolution(
    [1, 2, 3, 4],
    [5, 6, 7, 8],
)
