#include<stdio.h>
#include<stdlib.h>

struct  Data{
    int number;
    int height;
    Data*left, *right;
} *root = NULL;

Data*createData(int number){
    Data*temp = (Data*)malloc(sizeof(Data));
    temp->number = number;
    temp->left = temp->right = NULL;
    temp->height = 1;
    return temp;
}

int max(int a, int b){
    return a>b?a:b;
}

int height(Data*root){
    if(root == NULL) return 0;
    return root->height;
}

int getBalance(Data*root){
    if(root == NULL) return NULL;
    return height(root->left) - height(root->right);
}

Data*leftRotate(Data*root){
    Data* x = root;
    Data* y = root->right;
    Data* z = y->left;

    y->left = x;
    x->right = z;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; 
}

Data*rightRotate(Data*root){
    Data* x = root;
    Data* y = root->left;
    Data* z = y->right;

    y->right = x;
    x->left = z;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; 
}

Data*rotate(Data*root){
    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);
    if(balance > 1){
        if(getBalance(root->left) >= 0){
            return rightRotate(root);
        }
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }else if(balance < -1){
        if(getBalance(root->right) <= 0){
            return leftRotate(root);
        }
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Data*insert(Data*root, int number){
    if(root == NULL) root = createData(number);
    else if(number > root->number) root->right = insert(root->right, number);
    else root->left = insert(root->left, number);
    return rotate(root);
}

Data*predecessor(Data*root){
    Data*temp = root->left;
    if(temp->right!=NULL){
        temp = temp->right;
    }
    return temp;
}

Data* delData(Data*root, int number){
    if(root == NULL){
        printf("Data not found!\n");
        return root;
    }else if(number > root->number){
        root->right = delData(root->right, number);
    }else if(number < root->number){
        root->left =  delData(root->left, number);
    }else{//when root.number value is same as number value
        printf("Data Found!\n");
        if(root->left == NULL || root->right == NULL){
            Data*temp = root->left?root->left:root->right;
            if(temp == NULL){//when the delete target has no children
                temp = root;
                root = NULL;
            }
            else{//when the delete target has at least 1 children
                root = temp;
            }
            temp = NULL;
            free(temp);
        }else{//when the delete target has two children
            Data*temp = predecessor(root);
            printf("\nPRedecessor: %d\n", temp->number);
            root->number = temp->number;//changing the root value into it's predecessor value
            root->left = delData(root->left, temp->number);//delete the remaining predecessor value in root, and this is how extacly call the delData function
        }
    }
    if(root == NULL) return root;
    
    root = rotate(root);
    return root;
}

void justInsert(int number){
    root = insert(root, number);
}

void inorder(Data*root){
    if(root != NULL){
        inorder(root->left);
        printf("%d | %d, ", root->number, root->height);
        inorder(root->right);
    }
}



int main(){
    int inp = 0;
    int ins;
    while (inp != 4)
    {
        printf("1. Ins\n2. Prin\n3. Delete\n4. exit\n");
        printf("Your input>>");
        scanf("%d", &inp);
        switch (inp)
        {
        case 1:
            printf("Insert>>");
            scanf("%d", &ins);
            justInsert(ins);
            break;
        case 2:
            printf("This:\n");
            inorder(root);
            printf("\n");
            break;
        case 3:
            printf("Number to be deleted>>");
            scanf("%d", &ins);
            root = delData(root, ins);
            break;
        
        default:
            printf("Eror\n");
            break;
        
        printf("\n");
        }
    }
    return 0;
}