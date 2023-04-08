import matplotlib.pyplot as plt
import VanDerPol as vdp

def scatter_plot(x, y, show=True, xlabel='x', ylabel='p'):
    plt.scatter(x, y, s=10)
    plt.grid('--', linewidth=0.5)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    if show:
        plt.show()

def line_plot(x, y, show=True, xlabel='', ylabel=''):
    plt.plot(x, y, 'b')
    plt.grid('--', linewidth=0.5)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.show()
    if show:
        plt.show()

# First we solve the Van Der Pol equation for mu = 1
## We use Euler method
euler_mu1 = vdp.vdp_euler(1., 1., 1., 0.01, 15.)
x_e_mu1 = euler_mu1.getVariable_i(0)
y_e_mu1 = euler_mu1.getVariable_i(1)
scatter_plot(x_e_mu1, y_e_mu1)

## And then Runge-Kutta method
rk2_mu1 = vdp.vdp_rk2(1., 1., 1., 0.01, 15.)
x_rk2_mu1 = rk2_mu1.getVariable_i(0)
y_rk2_mu1 = rk2_mu1.getVariable_i(1)
scatter_plot(x_rk2_mu1, y_rk2_mu1)

## Then we overlap the two plots
scatter_plot(x_e_mu1, y_e_mu1, show=False)
scatter_plot(x_rk2_mu1, y_rk2_mu1)

# We now increase mu to 5
## Euler 
euler_mu5 = vdp.vdp_euler(1., 1., 5., 0.01, 15.)
x_e_mu5 = euler_mu5.getVariable_i(0)
y_e_mu5 = euler_mu5.getVariable_i(1)
scatter_plot(x_e_mu5, y_e_mu5)

## Runge-Kutta 
rk2_mu5 = vdp.vdp_rk2(1., 1., 5., 0.01, 15.)
x_rk2_mu5 = rk2_mu5.getVariable_i(0)
y_rk2_mu5 = rk2_mu5.getVariable_i(1)
scatter_plot(x_rk2_mu5, y_rk2_mu5)

## Overlapped
scatter_plot(x_e_mu5, y_e_mu5, show=False)
scatter_plot(x_rk2_mu5, y_rk2_mu5)

# If we further increase mu to 10 the difference between the two methods gets even larger
## Euler 
euler_mu10 = vdp.vdp_euler(1., 1., 10., 0.01, 20.)
x_e_mu10 = euler_mu10.getVariable_i(0)
y_e_mu10 = euler_mu10.getVariable_i(1)
scatter_plot(x_e_mu10, y_e_mu10)

## Runge-Kutta 
rk2_mu10 = vdp.vdp_rk2(1., 1., 10., 0.01, 20.)
x_rk2_mu10 = rk2_mu10.getVariable_i(0)
y_rk2_mu10 = rk2_mu10.getVariable_i(1)
scatter_plot(x_rk2_mu10, y_rk2_mu10)

## Overlapped
scatter_plot(x_e_mu10, y_e_mu10, show=False)
scatter_plot(x_rk2_mu10, y_rk2_mu10)

# This equation is stiff, and this means that it's highly dependent on the time step that we choose
# While the Euler method can give a decent approximation, provided that the time step is small enough, 
# the best numerical method for this type of equations is Runge-Kutta 
