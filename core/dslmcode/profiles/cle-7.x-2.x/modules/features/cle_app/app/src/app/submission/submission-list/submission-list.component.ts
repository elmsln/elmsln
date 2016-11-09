import { Component, OnInit } from '@angular/core';
import { SubmissionService } from '../../submission.service';

@Component({
  selector: 'cle-submission-list',
  templateUrl: './submission-list.component.html',
  styleUrls: ['./submission-list.component.css'],
  providers: [SubmissionService]
})
export class SubmissionListComponent implements OnInit {
  submissions: Array<any>;

  constructor(private submissionService: SubmissionService) { }

  ngOnInit() {
    this.submissionService.getSubmissions()
        .subscribe(data => {
          this.submissions = data;
          console.log(data);
        });
  }
}
