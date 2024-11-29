import numpy as np
from scipy.special import gamma
from scipy.special import eval_jacobi
from scipy.special import roots_jacobi

eps = np.finfo(float).eps

def JacobiGQ(N, alpha, beta):
    # Compute the roots (quadrature points) and weights using roots_jacobi
    x, w = roots_jacobi(N + 1, alpha, beta)

    # Adjust weights based on Jacobi polynomial properties
    factor = 2**(alpha + beta + 1) / (alpha + beta + 1)
    factor *= gamma(alpha + 1) * gamma(beta + 1) / gamma(alpha + beta + 1)
    w *= factor

    return x, w

def JacobianGL(N, alpha, beta):
    x = np.zeros(N + 1)
    x[0] = -1.0
    x[-1] = 1.0

    if(N == 1): return x

    xint,w = JacobiGQ(N-2, alpha+1, beta+1)
    x[1:-1] = xint

    return x

def GradJacobiP(N, alpha, beta, x):
    if N == 0:
        return np.zeros_like(x)  # Derivative of a constant is zero

    # Compute the Jacobi polynomial P_{N-1}^{(alpha+1, beta+1)}(x)
    P_Nm1 = eval_jacobi(N - 1, alpha + 1, beta + 1, x)

    # Scaling factor for the derivative
    scale_factor = 0.5 * (N + alpha + beta + 1)

    # Derivative in orthonormal form
    norm_factor = np.sqrt(
        (2 * N + alpha + beta + 1) /
        (2**(alpha + beta + 1) *
         gamma(N + alpha + 1) * gamma(N + beta + 1) /
         gamma(N + alpha + beta + 1))
    )
    dP = scale_factor * norm_factor * P_Nm1

    return dP

def GradVandermonde1D(N, r):
    Nc = r.shape[0]

    DVr = np.zeros((Nc, N+1))

    for j in range(N+1):
        DVr[:,j] = GradJacobiP(j, 0, 0, r)
    
    return DVr

def Vandermonde1D(N, r):
    Nc = r.shape[0]

    V1D = np.zeros((Nc, N+1))

    for j in range(N+1):
        V1D[:,j] = eval_jacobi(j,0,0,r)
    return V1D

N = 7

r = JacobianGL(N, 0, 0)
V = Vandermonde1D(N,r)
Vr = GradVandermonde1D(N,r)
invV = np.linalg.inv(V)

Dr = np.matmul(Vr, invV)

print(Dr)