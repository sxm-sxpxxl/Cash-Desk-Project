object MainForm: TMainForm
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'Cash desk modulation program'
  ClientHeight = 262
  ClientWidth = 629
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 375
    Top = 8
    Width = 225
    Height = 25
    AutoSize = False
    Caption = 'Number of serviced clients: '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'GOST type B'
    Font.Style = []
    ParentFont = False
  end
  object NumberOfServicedClientsLabel: TLabel
    Left = 606
    Top = 8
    Width = 14
    Height = 32
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -29
    Font.Name = 'GOST type B'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 375
    Top = 40
    Width = 225
    Height = 25
    AutoSize = False
    Caption = 'Size queue:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'GOST type B'
    Font.Style = []
    ParentFont = False
  end
  object SizeQueueLabel: TLabel
    Left = 606
    Top = 40
    Width = 14
    Height = 32
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -29
    Font.Name = 'GOST type B'
    Font.Style = []
    ParentFont = False
    OnClick = AddClientButtonClick
  end
  object AddClientButton: TButton
    Left = 375
    Top = 228
    Width = 245
    Height = 25
    Caption = 'Add client'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'GOST type B'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = AddClientButtonClick
  end
  object StartButton: TButton
    Left = 375
    Top = 166
    Width = 245
    Height = 25
    Caption = 'Start'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'GOST type B'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = StartButtonClick
  end
  object CountCashierRadioGroup: TRadioGroup
    Left = 375
    Top = 71
    Width = 245
    Height = 89
    Caption = 'Count of cashier'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'GOST type B'
    Font.Style = []
    ItemIndex = 0
    Items.Strings = (
      '1'
      '2'
      '3')
    ParentFont = False
    TabOrder = 2
    OnClick = CountCashierRadioGroupClick
  end
  object StopButton: TButton
    Left = 375
    Top = 197
    Width = 245
    Height = 25
    Caption = 'StopButton'
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'GOST type B'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = StopButtonClick
  end
  object ThreadInfoListBox: TListBox
    Left = 8
    Top = 8
    Width = 361
    Height = 245
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'GOST type B'
    Font.Style = []
    ItemHeight = 17
    ParentFont = False
    TabOrder = 4
  end
  object Update: TTimer
    Interval = 100
    OnTimer = UpdateTimer
    Left = 479
    Top = 109
  end
  object AddToQueue: TTimer
    Enabled = False
    Interval = 500
    OnTimer = AddToQueueTimer
    Left = 551
    Top = 109
  end
end
