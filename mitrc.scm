(define (sqr x)(* x x))

(define (fibo x)
    (if (< x 2)
        1
        (+ (fibo (- x 1)) (fibo (- x 2)))
    )
)

(difine (fibo_list_20)
    (map fibo '(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20))
)
