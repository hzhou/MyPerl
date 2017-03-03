### For Impatient
    cd cmp
    gcc -g -o myperl myperl-170303.c -lm -lpcre
    -- create your test script as t.pl
    ./myperl 

### For Curious
    Get and install [MyDef](https://github.com/hzhou/MyDef)
    Get and install [output_c](https://github.com/hzhou/output_c)
    -- There are some doc in those repositories, but feel free to ask

    mydef_make    # creates config and Makefile, answer out/ and C (output folder and language module)
    make          # compiles from .def sources to out/myperl.c
    -- create a simple out/Makefile
    mydef_make    # to integrate sub makefile

    -- read def sources [start with main.def, macros/parse_frame.def, ... follow the trail]
    -- make changes then make and run:
    make all && out/myperl

### Plan
The goal for the main branch is to implement a subset of Perl, which will run all my useful Perl code. I useful Perl code spans over a decade, so aiming at this goal, I hope it will result in a very useful Perl alternative. 

The main branch will focus on readability. While it does emphasize on correctness and speed, it does not try to entirely emulate Perl 5. It will only include necessary features (my say). Generally I will not accept pull requests on this branch (unless the contributor shares my philosophy).

I am open to add branches or forks for production branch(es) that aim to full compatibility of Perl 5, or add any features or fix behaviors, and accept contributions. In fact, it is best if there are developer who want to take ownerships for them. 
    




