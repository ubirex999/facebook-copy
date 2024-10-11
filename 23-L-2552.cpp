#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;
class Object;
class User;
class Page;
class Date;
class Comments;
class Activity;
class PostContent;
class Post;
class Controller;

class Helper
{
    // contains all helping fucntions used in the code
public:
    static void strCopy(char*& arr1, const char* arr2)
    {
        if (arr1)
        {
            delete[] arr1;
        }
        int len = strlen(arr2);
        arr1 = new char[len + 1];
        for (int i = 0; i <= len; i++) {
            arr1[i] = arr2[i];
        }
    }


    static char* GetStringFromBuffer(char* arr)
    {
        char* temp = new char[strlen((arr)) + 1];
        strCopy(temp, arr);
        return temp;
    }

    static bool Search(const char* subString, const char* String)
    {
        int subLen = strlen(subString);
        int strLen = strlen(String);

        for (int i = 0; i <= strLen - subLen; i++)
        {
            bool found = true;
            for (int j = 0; j < subLen; j++)
            {
                if (subString[j] != String[i + j])
                {
                    found = false;
                    break;
                }
            }

            if (found)
            {
                return true;
            }
        }
        return false;
    }

    static bool CompareString(const char* str1, const char* str2)
    {
        int len1 = strlen(str1);
        int len2 = strlen(str2);
        int i = 0;
        while (i < len1 && i < len2)
        {
            if (str1[i++] != str2[i++])
                return false;
        }
        return true;
    }
};

class Date
{
    int day;
    int month;
    int year;
public:
    Date(int d = 0, int m = 0, int y = 0) // simple constructor
    {
        day = d;
        month = m;
        year = y;
    }

    void SetDate(int d, int m, int y) // setter
    {
        day = d;
        month = m;
        year = y;
    }
    void  ViewDate()
    {
        cout << "    (" << day << " / " << month << " / " << year << ")" << endl;
    }

};

class Object
{
    char* ID;
protected:
    Post** Timeline;
    int totalTimelines;
public:
    Object() : ID(0), totalTimelines(0)
    {
        Timeline = new Post * [10];
    }

    ~Object()
    {
        for (int i = 0; i < totalTimelines; i++)
        {
            delete Timeline[i];
        }
        delete[]Timeline;
    }

    void SetID(char* id) // setter
    {
        Helper::strCopy(ID, id);
    }

    char* GetID() // getter
    {
        return ID;
    }

    void AddTimeline(Post* obj)  // add timeline
    {
        Timeline[totalTimelines++] = obj;
    }

    virtual void ViewTimeline() //  empty virtual fucntion
    {

    }
    virtual void ViewName() //  empty virtual fucntion
    {

    }

    virtual void CommentOnAPost(Post* postptr, Comments* commentptr)
    {

    }

};

class Page : public Object
{
    char* Title;
    Comments** commentsList;
    int commentsCount;
public:

    Page()
    {
        Title = nullptr;
        commentsList = nullptr;
        commentsCount = 0;
    }

    ~Page()
    {
        delete[] Title;
    }

    char* GetPageTitle()
    {
        return Title;
    }

    void ReadDataFromFile(fstream& fin)
    {
        char* temp = new char[100];
        fin.getline(temp, 101);
        this->SetID(Helper::GetStringFromBuffer(temp));
        temp = new char[100];
        fin.getline(temp, 101);
        Title = Helper::GetStringFromBuffer(temp);
        delete[]temp;
    }

    void ViewTimeline();

    void SetCurrentPage()
    {
        cout << endl << "Command: \t Set currrent Page " << GetID() << endl;
        cout << Title << " is successfully set as current Page." << endl;
    }

    void ViewName() //  empty virtual fucntion
    {
        cout << Title;
    }

};

class User : public Object
{
    char* Fname;
    char* Lname;
    User** FriendList;
    Page** LikedPages;
    int usercount;
    int pagecount;

public:
    int GetFriends()
    {
        return usercount;
    }

    int GetLikes()
    {
        return pagecount;
    }

    User** GetFriendList()
    {
        return FriendList;
    }

    Page** GetLikedPages()
    {
        return LikedPages;
    }

    User()
    {
        Fname = nullptr;
        Lname = nullptr;
        FriendList = nullptr;
        LikedPages = nullptr;
        usercount = 0;
        pagecount = 0;
    }

    ~User()
    {
        delete[] Fname;
        delete[] Lname;

        delete[] FriendList;

        delete[] LikedPages;


    }

    User(User& other)
    {
        Helper::strCopy(Fname, other.Fname);
        Helper::strCopy(Lname, other.Lname);
    }

    void ReadDataFromFile(fstream& fin)
    {
        char* temp = new char[100];
        fin.getline(temp, 101);
        this->SetID(Helper::GetStringFromBuffer(temp));
        temp = new char[100];
        fin.getline(temp, 101);
        Fname = Helper::GetStringFromBuffer(temp);
        temp = new char[100];
        fin.getline(temp, 101);
        Lname = Helper::GetStringFromBuffer(temp);
        delete[]temp;
    }

    void AddFriend(User*& obj)
    {

        if (obj == 0)
        {
            return;
        }
        else if (usercount == 10)
        {
            cout << " no more friends can be added !" << endl;
            return;
        }
        usercount++;

        if (FriendList != 0)
        {
            User** templist = new User * [usercount];

            for (int i = 0; i < usercount; i++)
            {
                templist[i] = FriendList[i];
            }
            templist[usercount - 1] = obj;

            delete[] FriendList;
            FriendList = templist;
        }
        else
        {
            FriendList = new User * [1];
            FriendList[0] = obj;
        }

    }

    void LikePage(Page*& page)
    {

        if (pagecount == 0)
        {
            LikedPages = new Page * [1];
            LikedPages[0] = page;
            pagecount++;
            return;
        }
        else if (pagecount == 10)
        {
            cout << " no more pages can be liked !" << endl;
            return;
        }
        pagecount++;

        if (LikedPages != 0)
        {
            Page** templist = new Page * [pagecount];

            for (int i = 0; i < pagecount - 1; i++)
            {
                templist[i] = LikedPages[i];

            }
            templist[pagecount - 1] = page;

            delete[] LikedPages;
            LikedPages = templist;
        }
        else
        {
            LikedPages = new Page * [1];
            LikedPages[0] = page;
        }


    }

    void SetCurrentUser()
    {
        cout << endl << "Command: \t Set currrent user " << GetID() << endl;
        cout << Fname << " " << Lname << " is successfully set as current user." << endl;
        ViewFriendList();
        ViewLikedPages();
    }

    void ViewFriendList()
    {
        cout << "---------------------------------" << " \n\nCommand: View Friend List \n\n" << "--------------------------------------" << endl;
        cout << this->Fname << " " << this->Lname << "Friend List : " << endl;
        int i = this->usercount;
        for (int j = 0; j < i; j++)
        {
            cout << this->FriendList[j]->GetID() << "--" << this->FriendList[j]->Fname << " " << this->FriendList[j]->Lname << endl;
        }
    }

    void ViewLikedPages()
    {
        cout << "-----------------------------------" << "\n\nCommand :  View Liked Pages \n\n" << "-------------------------------------" << endl;
        cout << Fname << " " << Lname << " Liked Pages : " << endl;
        for (int i = 0; i < this->pagecount; i++)
        {
            if (LikedPages[i] != nullptr)
            {
                cout << this->LikedPages[i]->GetID() << "--" << this->LikedPages[i]->GetPageTitle() << endl;
            }
            else
            {
                cout << "Page at index " << i << " is nullptr" << endl;
            }
        }
    }

    void ViewTimeline();

    void ViewName()
    {
        cout << Fname << " " << Lname;
    }

};

class Comments
{
private:
    char* description;
    User* commentBy;
public:
    Comments()
    {
        description = 0;
        commentBy = nullptr;
    }

    void SeComment(char* txt, User* ptr)
    {
        commentBy = ptr;
        Helper::strCopy(description, txt);
    }

    void SeeComment()
    {
        if(commentBy != 0)
            commentBy->ViewName();
        cout << ":\n";
        cout << "\t\t\t\"" << description << "\"" << endl;
    }


};

class Activity
{
    int Typeofactivity;
    char* Valueofactivity;
public:
    Activity()
    {
        Typeofactivity = 0;
        Valueofactivity = 0;
    }

    void SetActivity(int& type, char* Value)
    {
        Typeofactivity = type;

        Helper::strCopy(Valueofactivity, Value);
    }

    void SeeActivity()
    {
        if (Typeofactivity == 1)
        {
            cout << " is feeling " << Valueofactivity;
        }
        if (Typeofactivity == 2)
        {
            cout << " is thinking about " << Valueofactivity;
        }
        if (Typeofactivity == 3)
        {
            cout << " is making " << Valueofactivity;
        }
        if (Typeofactivity == 4)
        {
            cout << " is celebrating  " << Valueofactivity;
        }
    }
};

class PostContent
{

};

class Post : public PostContent
{
    char* Post_ID;
    char* PostText;
    Date ShareDate;
    Object* SharedBy;
    Object** LikedBy;
    Comments** comments;
    char * memorytext;
    int yeardiff;
    int Likes;
    int CommentsCount;
    Activity* allactivities;
public:
    Post()
    {
        Post_ID = 0;
        PostText = 0;
        SharedBy = 0;
        CommentsCount = 0;
        memorytext  = 0;
        yeardiff = 0;
        Likes = 0;
        allactivities = 0;

        LikedBy = new Object * [10];
        comments = new Comments * [10];
        for (int i = 0; i < 10; i++)
        {
            LikedBy[i] = nullptr;
            comments[i] = nullptr;
        }

    }

    void ReadDataFromFile(fstream& fin) {


        char* temp = new char[100];
        fin.getline(temp, 100);
        Post_ID = Helper::GetStringFromBuffer(temp);
        delete[]temp;
        int d, m, y;
        fin >> d;
        fin >> m;
        fin >> y;
        fin.ignore();
        ShareDate.SetDate(d, m, y);
        temp = new char[100];
        fin.getline(temp, 100);
        PostText = Helper::GetStringFromBuffer(temp);

        delete[]temp;
    }

    void SetSharedBy(Object*& s) {
        SharedBy = s;
    }

    void AddLikes(Object* obj) {
        if (!LikedBy) {
            LikedBy = new Object * [10];
            Likes = 0;
        }
        LikedBy[Likes] = obj;
        Likes++;
    }

    void ViewPost()
    {
        //if (allactivities != nullptr)
        {

            ShareDate.ViewDate();

            cout << "     " << PostText << endl;
        }
    }

    void ViewLikeList() {
        cout << "------------------------------------------------"<<endl;
        cout << "Command  :: ViewLikeList " << Post_ID << " " << endl;
        cout << "-------------------------------------------------"<<endl;

        cout << "\n  Liked by :: \n";
        for (int i = 0; i < Likes; i++) {
            cout << LikedBy[i]->GetID() << "-----";
            LikedBy[i]->ViewName();
            cout << endl;
        }


    }

    void SEEActivity()
    {
        if(allactivities != 0)
            allactivities->SeeActivity();
    }

    char* GetPostID()
    {
        return Post_ID;
    }

    void AddComments(Comments* c)
    {

        comments[CommentsCount] = c;
        CommentsCount++;
    }

    void Addactivity(Activity* allactivities)
    {
        this->allactivities = allactivities;

    }

    void SEEComments()
    {
        for (int i = 0;i < CommentsCount;i++)
        {
            comments[i]->SeeComment();
        }
    }
};

class Controller {

    User** AllUsers;
    Page** AllPages;
    Post** AllPosts;

    int totalUsers;
    int totalPages;
    int totalPosts;
    int totalComments;
    int totalActivities;


public:

    void sharememory( char * Postid , char * mtext  )
    {
        Post *temppost = SearchPostByID(Postid);

    }
    ~Controller()
    {
        for (int i = 0; i < totalUsers; i++)
        {
            delete AllUsers[i];
        }
        delete[]AllUsers;

        for (int i = 0; i < totalPages; i++)
        {
            delete AllPages[i];
        }
        delete[]AllPages;



    }

    void LoadAllUsers(fstream& fin)
    {
        totalUsers = 0;
        fin >> totalUsers;
        fin.ignore();
        AllUsers = new User * [totalUsers];

        for (int i = 0; i < totalUsers; i++)
        {
            AllUsers[i] = new User();
            AllUsers[i]->ReadDataFromFile(fin);
        }
    }

    void LoadAllPages(fstream& fin)
    {
        totalPages = 0;
        fin >> totalPages;
        fin.ignore();
        AllPages = new Page * [totalPages];

        for (int i = 0; i < totalPages; i++)
        {
            AllPages[i] = new Page();
            AllPages[i]->ReadDataFromFile(fin);

        }
    }

    void LinkUsersAndPages(fstream& fin)
    {
        char temp[100];
        fin.getline(temp, 100);

        for (; temp[0] != '-'; )
        {

            User* TempUser = SearchUserByID(temp);

            fin.getline(temp, 100);

            while (strcmp(temp, "-1") != 0)
            {
                User* TempFriend = SearchUserByID(temp);

                if (TempFriend)
                {
                    TempUser->AddFriend(TempFriend);

                }
                fin.getline(temp, 100);
            }


            fin.getline(temp, 100);
            while (strcmp(temp, "-1") != 0)
            {
                Page* TempPage = SearchPageByID(temp);

                if (TempPage)
                    if (temp != 0)
                        TempUser->LikePage(TempPage);
                fin.getline(temp, 100);
            }
            fin.getline(temp, 100);
        }

    }

    void LoadAllPosts(fstream& fin)
    {
        fin >> totalPosts;
        fin.ignore();
        AllPosts = new Post * [totalPosts];
        for (int i = 0;i < totalPosts;i++)
        {
            AllPosts[i] = new Post();
            AllPosts[i]->ReadDataFromFile(fin);
            Object* Ptr = nullptr;
            char* temp = new char[100];
            fin.getline(temp, 100);
            Ptr = SearchObject(Helper::GetStringFromBuffer(temp));
            AllPosts[i]->SetSharedBy(Ptr);
            Ptr->AddTimeline(AllPosts[i]);
            temp = new char[100];
            fin.getline(temp, 100);
            while (Helper::CompareString(temp, "-1") == 0)
            {

                Ptr = SearchObject(Helper::GetStringFromBuffer(temp));
                AllPosts[i]->AddLikes(Ptr);
                temp = new char[100];
                fin.getline(temp, 100);

            }

        }

    }

    void LoadData() {
        fstream fin("user.txt");
        if (!fin) {
            cout << "Error opening file users.txt " << endl;
        }
        LoadAllUsers(fin);
        fin.close();

        fin.open("page.txt");
        if (!fin) {
            cout << "Error opening file pages.txt " << endl;
        }
        LoadAllPages(fin);
        fin.close();


        fin.open("link.txt");
        if (!fin) {
            cout << "Error opening file Links.txt" << endl;
        }
        LinkUsersAndPages(fin);
        fin.close();

        fin.open("POST.txt");
        if (!fin)
        {
            cout << "Error opening Posts.txt" << endl;
            return;
        }
        LoadAllPosts(fin);
        fin.close();

        fin.open("comments.txt");
        if (!fin)
        {
            cout << "Error opening comments.txt" << endl;
            return;
        }
        LoadAllComments(fin);
        fin.close();

        fin.open("socialactivities.txt");
        if (!fin)
        {
            cout << "Error opening social activities.txt" << endl;
            return;
        }
        LoadAllSocialActivities(fin);
        fin.close();




    }

    void LoadAllComments(fstream& fin)
    {
        fin >> totalComments;

        fin.ignore();
        char temp[100];

        for (int i = 0; i < totalComments; i++)
        {
            Comments* AllComments = new Comments();


            fin.getline(temp, 100);
            Post* Postptr = SearchPostByID(temp);
            fin.getline(temp, 100);
            User* Objptr = SearchUserByID(temp);
            fin.getline(temp, 100);
            AllComments->SeComment(temp, Objptr);
            Postptr->AddComments(AllComments);
        }
    }

    void LoadAllSocialActivities(fstream& fin)
    {
        fin >> totalActivities;
        fin.ignore();

        char temp[100];
        int temp1;

        for (int i = 0; i < totalActivities; i++)
        {

            Activity* Allactivities = new Activity;
            fin.getline(temp, 100);
            fin >> temp1;
            fin.ignore();
            Post* PostPtr = SearchPostByID(temp);
            fin.getline(temp, 100);
            (Allactivities->SetActivity(temp1, temp));
            PostPtr->Addactivity(Allactivities);
        }


    }

    User* SearchUserByID(const char* ID)
    {

        for (int i = 0;i < totalUsers;i++)
        {

            if (Helper::Search(ID, AllUsers[i]->GetID()))
            {
                return AllUsers[i];
            }
        }
        return nullptr;
    }

    Page* SearchPageByID(const char* ID)
    {
        for (int i = 0;i < totalUsers;i++)
        {

            if (Helper::Search(ID, AllPages[i]->GetID()))
            {
                return AllPages[i];
            }
        }
        return nullptr;

    }

    Object* SearchObject(const char* str)
    {
        Object* Ptr;
        if (*str == 'u')
            Ptr = SearchUserByID(str);
        else Ptr = SearchPageByID(str);
        return Ptr;
    }

    void SetCurrentObject(const char* str)
    {
        if (*str == 'u' || *str == 'U')
        {
            User* user = SearchUserByID(str);
            user->SetCurrentUser();
            Object* temp = user;
            temp->ViewTimeline();
        }
        else
        {
            Page* user = SearchPageByID(str);
            user->SetCurrentPage();
            Object* temp = user;
            temp->ViewTimeline();
        }
    }

    void ViewPage(const char* str)
    {
        if (*str == 'p' || *str == 'P')
        {
            Page* user = SearchPageByID(str);
            user->SetCurrentPage();
            Object* temp = user;
            temp->ViewTimeline();
        }
        else
            cout << "INVALID PAGE ID!" << endl;
    }

    void SetCurrentPost(const char* str)
    {
        if (*str == 'p' || *str == 'P')
        {
            Post* user = SearchPostByID(str);
            user->ViewLikeList();
        }
        else {
            cout << "INVALID Post ID!" << endl;
        }
    }

    Post* SearchPostByID(const char* ID)
    {
        for (int i = 0;i < totalPosts;i++)
        {
            if (Helper::Search(ID, AllPosts[i]->GetPostID()))
                return AllPosts[i];
        }
        return nullptr;

    }

    void Commentposting(const char* str, const char* IDofpost, const char* comment)
    {
        Object* objptr = this->SearchObject(str);
        Post* ptr = this->SearchPostByID(IDofpost);
        Comments* cptr = new Comments();


    }

    void Run()
    {
        User* userptr;
        userptr = SearchUserByID("u5");
    }

    void ViewHome(const char* str)
    {
        cout << "Command: ViewHome(" << str << ")" << endl;
        {

            User* ptr = SearchUserByID(str);
            ptr->ViewTimeline();
            for (int i = 0;i < ptr->GetFriends();i++) {
                ptr->GetFriendList()[i]->ViewTimeline();
            }
            ptr->ViewTimeline();
            for (int i = 0;i < ptr->GetLikes();i++)
            {
                ptr->GetLikedPages()[i]->ViewTimeline();
            }
        }
    }


};

void Page::ViewTimeline()
{
    cout << "------------------------------"<<endl;
    for (int i = 0;i < totalTimelines;i++)
    {
        cout << Title;
        Timeline[i]->SEEActivity();
        Timeline[i]->ViewPost();
        Timeline[i]->SEEComments();
        cout << endl << endl;
    }
}

void User::ViewTimeline() {
    cout << "-------------------------------"<<endl;
    for (int i = 0; i < totalTimelines; i++) {
        cout << Fname << " " << Lname;
        Timeline[i]->SEEActivity();
        Timeline[i]->ViewPost();
        Timeline[i]->SEEComments();
        cout << endl;
    }

}

int main()
{
    Controller mainApp;
    mainApp.LoadData();
    cout << "--------------------------------";
    cout << "Command: View TimeLine" << endl;
    cout << "--------------------------------";
    mainApp.SetCurrentObject("u7");
    mainApp.ViewHome("u7");
    mainApp.SetCurrentPost("post5");
    mainApp.Run();

    return 0;
}

