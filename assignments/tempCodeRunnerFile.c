  for (i = 0; i < num_ele; i++)
    {
        scanf("%d %d", &row, &col); 
        push(&ele_arr[i].memory, row - 1, col - 1);
    }