#include<iostream>
#include<string>
using namespace std;

class Note
{
    friend class Index;
    private:
        string subject;
        float note;
    public:
        Note(string subject_in="unspecified", float note_int=2.0):
        subject(subject_in), note(note_int){};

        void SetSubject(string subject_in)
        {
            subject=subject_in;
        }
        void SetNote(float note_in)
        {
            if(note_in==2.0||note_in==2.5||note_in==3.0||note_in==3.5||note_in==4.0||note_in==4.5||note_in==5.0)
                note=note_in;
            else
                cout<<"Please input correct value.";
            return;
        }
        string GetSubject()
        {
            return subject;
        }

        float GetNote()
        {
            return note;
        }
        
        void Show()
        {
            cout<<subject<<" "<<note<<endl;
            return;
        }
};

class Index
{
    int NoteCount;
    Note *NoteArray = new Note[NoteCount];

    public:
        Index(int n_notes_in):NoteCount(n_notes_in)
        {
            NoteArray = new Note[NoteCount];
        };
        ~Index()
        {
            delete[] NoteArray;
        }
        void Set(int NoteIndex, string subject_in, float note_in)
        {
            if(NoteIndex>=0&&NoteIndex<NoteCount)
            {
                NoteArray[NoteIndex].SetNote(note_in);
                NoteArray[NoteIndex].SetSubject(subject_in);
                return;
            }
            else
            {

            }
        }

        void Change(float note_in, string subject_in)
        {
            for(int i=0;i<NoteCount;i++)
            {
                if(NoteArray[i].GetSubject()==subject_in)
                {
                    NoteArray[i].SetNote(note_in);
                    break;
                }
            }
            return;
        }

        float Average()
        {
            if(NoteCount==0)
            {
                return 0;
            }
            float sum{0.0};
            for(int i=0;i<NoteCount;i++)
            {
                sum+=NoteArray[i].note;
            }
            return (sum/NoteCount);
        }
        void Show()
        {
            cout<<"~~~~~~Index~~~~~~"<<endl;
            for(int i=0;i<NoteCount;i++)
            {
                cout<<i+1<<". ";
                NoteArray[i].Show();
                cout<<endl;
            }
            cout<<"AVERAGE: "<<Average()<<endl;
            cout<<"~~~~~~~~~~~~~~~~~"<<endl;
        }

        void Add(string subject_in, float note_in);
        void Remove(string subject_in);
        friend float FindNote(string subject_in, Index *Index_in);


};

void Index::Add(string subject_in, float note_in)
{
    Note *NewNotesArray= new Note[NoteCount+1];
    for(int i = 0; i < NoteCount; i++)
    {
        NewNotesArray[i]=NoteArray[i];
    }
    delete[] NoteArray;
    NoteArray=NewNotesArray;
    NoteCount++;

    NoteArray[NoteCount-1].subject=subject_in;
    NoteArray[NoteCount-1].SetNote(note_in);
    return;
    
}

void Index::Remove(string subject_in)
{
    int Index=-1;

    for(int i=0;i<NoteCount;i++)
    {
        if(NoteArray[i].GetSubject()==subject_in)
        {
            Index=i;
            break;
        }
        if(Index<0)
        return;

        Note *NewNoteArray= new Note[NoteCount-1];
        for(int i=0;i<Index;i++)
        {
            NewNoteArray[i]=NoteArray[i];
        }

        for(int i=Index+1;i<NoteCount;i++)
        {
            NewNoteArray[i-1]=NoteArray[i];
        }
        delete[] NoteArray;
        NoteArray=NewNoteArray;
        NoteCount--;

        return;
    }
}

float FindNote(string subject_in, Index *index_in)
{
    for(int i=0;i<index_in->NoteCount;i++)
    {
        if(subject_in==index_in->NoteArray[i].GetSubject())
            return index_in->NoteArray[i].GetNote();

    }
    return 0.0;
}

int main()
{
    Index ind(3);
    ind.Set(0,"Analysis",3);
    ind.Set(1,"Algebra",4);
    ind.Set(2,"Physics",4);
    ind.Show();

    cout<<"Note from Algerbra: "<<FindNote("Algebra",&ind)<<endl;
    ind.Change(3,"Algebra");
    ind.Show();
    ind.Add("C++ Programming",5);
    ind.Show();
    ind.Remove("Physics");
    ind.Show();
    
    return 0;
}