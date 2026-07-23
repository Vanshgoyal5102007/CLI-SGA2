#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

struct Employee {
    int id;
    char name[30];
};

int main() {
    int fd = open("employees.dat", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0) { return 1; }

    struct Employee e1 = {1, "Alice"};
    struct Employee e2 = {2, "Bob"};
    write(fd, &e1, sizeof(struct Employee));
    write(fd, &e2, sizeof(struct Employee));

    struct Employee updated_e2 = {2, "Robert"};
    lseek(fd, sizeof(struct Employee), SEEK_SET); 
    write(fd, &updated_e2, sizeof(struct Employee));

    struct Employee read_emp;
    lseek(fd, sizeof(struct Employee), SEEK_SET);
    read(fd, &read_emp, sizeof(struct Employee));
    printf("Retrieved: ID=%d, Name=%s\n", read_emp.id, read_emp.name);

    close(fd);
    return 0;
}