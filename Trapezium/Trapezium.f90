function f(x_in) result(f_out)
    use, intrinsic :: iso_fortran_env, only: dp=>real64
    real(dp), intent(in) :: x_in
    real(dp) :: f_out
    ! edit line below to change function being integrated
    f_out = x_in**2
end function f



program trapezium_rule
    use, intrinsic :: iso_fortran_env, only: dp=>real64
    implicit none
    real(dp) :: f, x, x_min, x_max, delta, final_sum
    integer :: i, segments ! minimum 2
    
    x_min = 0
    x_max = 1
    segments =100
    delta = (x_max-x_min)/segments
  
    ! sum over all segments
    final_sum = f(x_min) + f(x_max)
    do i = 1, segments, 1
        x = x_min+i*delta
        final_sum = final_sum+2*f(x) 
    end do
    final_sum = (real(1,dp)/real(2,dp))*delta*final_sum
    ! output final value
    print *, final_sum

end program trapezium_rule

