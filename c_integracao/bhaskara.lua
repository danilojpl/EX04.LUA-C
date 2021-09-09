function bhaskara(a,b,c)
    x = (b^2)-(4*a*c)
    if (x<0) then
        print("raiz negativa!")
    else
        x = x^(1/2)
        return (-b+x)/(2*a), (-b-x)/(2*a)
    end 
end

