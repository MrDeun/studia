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
};

class Index
{
    int NoteCount;
    Note *NoteTable = new Note[NoteCount];
        Index(int n_notes_in):NoteCount(n_notes_in)
        {
            NoteTable = new Note[NoteCount];
        };
        ~Index()
        {
            delete[] NoteTable;
        }
        void Set(int NoteIndex, string subject_in, float note_in)
        {
            if(NoteIndex>=0&&NoteIndex<NoteCount)
            {
                NoteTable[NoteIndex].SetNote(note_in);
                NoteTable[NoteIndex].SetSubject(subject_in);
            }
        }

        void Change(float note_in, string subject_in)
        {
            for(int i=0;i<NoteCount;i++)
            {
                if(NoteTable[i].GetSubject()==subject_in)
                {
                    NoteTable[i].SetNote(note_in);
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
                sum+=NoteTable[i].note;
            }
            return (sum/NoteCount);
        }


};

int main()
{
    cout<<"PROGRAM OK";
    return 0;
}