#ifndef LEGEND_H
#define LEGEND_H


class Legend
{
    public:
        Legend();
        virtual ~Legend();
        /*
      property Top : integer read FTop write SetTop;
      property Left : integer read FLeft write SetLeft;
      property Height : integer read FHeight write SetHeight;
      property Width : integer read FWidth write SetWidth;
      property Font : TFont read FFont write SetFont;
      property Visible : boolean read FVisible write SetVisible;
      property BcgndColor : TColor read FBcgndColor write SetBcgndColor;
      property BorderColor : TColor read FBorderColor write SetBorderColor;
      property SampleWidth : integer read FSampleWidth write SetSampleWidth;
      property SampleLength : integer read FSampleLength write SetSampleLength;
      property SampleGap : integer read FSampleGap write SetSampleGap;
      property ItemGap : integer read FItemGap write SetItemGap;
      property Margin : integer read FMargin write SetMargin;
      property BorderWidth : integer read FBorderWidth write SetBorderWidth;
      property Bmp : TBitmap read FBmp;

      procedure CalcSize();
      procedure Draw();

      FStartX : array of array of integer;
        */
        void draw();

    protected:

    private:
        int top;
        int left;
        int height;
        int width;
        bool isVisible;

        void calcSize();
};

#endif // LEGEND_H
