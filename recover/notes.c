
Open memory card
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 2;
    }
Repeat until end of card

    Read 512 bytes into Buffer
    while (fread(block, sizeof(*block), 1, input) == sizeof(*block))

    If start of new jpeg
    if (block[0] == 0xff || block[1] == 0xd8 || block[2] == 0xff || ((block[3] & 0xf0) == 0xe0))

        If first jpeg
        if (count == 0)
            ....

        Else if more than 1 jpeg
        else if (count > 0 && count <= 50)

    If no jpeg (0 bytes)
        If already found jpeg
        if (count > 0)
        fclose(output);
