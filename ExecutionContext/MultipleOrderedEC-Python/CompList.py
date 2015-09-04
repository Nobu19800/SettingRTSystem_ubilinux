from OpenRTM_aist import RTC

CompList = [
    [
        [
            ["Test10", RTC.INACTIVE_STATE],
            ["Test20", RTC.ACTIVE_STATE]
        ],
        [
            [
                ["Test20", "Test30"],
                ["Test10"]
            ],
            [
                ["Test10"]
            ]
        ]
    ],
    [
        [
            ["Test10",RTC.ERROR_STATE],
            ["Test30",RTC.ACTIVE_STATE]
        ],
        [
            [
                
                ["Test20","Test10","Test30"],
                ["Test10","Test20"]
                
            ]
        ]
    ]
]
